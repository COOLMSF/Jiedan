#define FUSE_USE_VERSION 26

// Linux的头文件，提供错误处理
#include <errno.h>

// Libfuse的头文件，提供相应的数据结构和函数
#include <fuse.h>

// 标准库函数
#include <stdlib.h>

// 标准输入输出函数,提供scanf、printf基本函数
#include <stdio.h>

// 字符串处理
#include <string.h>

// 系统函数
#include <unistd.h>

// 文件操作函数
#include <fcntl.h>

// 文件属性函数
#include <sys/stat.h>

// 获取系统事件
#include <sys/time.h>

// 获取事件
#include <libgen.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// 限制
#include <linux/limits.h>

#define BLOCKSIZE 4096

// 写属性
#define O_WRITE(flags) ((flags) & (O_RDWR | O_WRONLY))
// 读属性
#define O_READ(flags)  (((flags) & (O_RDWR | O_RDONLY)) | !O_WRITE(flags))

// 文件访问时间
#define U_ATIME (1 << 0)

// 文件创建时间
#define U_CTIME (1 << 1)

// 文件修改时间
#define U_MTIME (1 << 2)

// 文件系统数据结构
struct filesystem {
	// 节点
  struct node *root;
};

// 文件操作
struct filehandle {
  struct node *node;
  int o_flags;
};

struct filesystem the_fs;

// 目录数据结构
struct direntry {
	// 目录名称
  char             name[PATH_MAX];
  struct node     *node;
  // 下一个入口
  struct direntry *next;
};

// 节点数据结构
struct node {
	// 节点属性
  struct stat   vstat;

	// 节点数据
  void         *data;

	// 文件描述符数量
  unsigned int  fd_count;
	// 删除前关闭文件
  int           delete_on_close;
};

// 添加目录
int AddDir(struct node *dir, struct direntry *entry, int replace, int *added);

// 分配目录
int DirAlloc(struct node *dir, const char *name, struct node *node, int replace);

// 删除目录
int RemoveDir(struct node *dir, const char *name);
// 查找目录
int FindDir(struct node *dir, const char *name, int namelen, struct direntry **entry);

// 获取节点信息
int GetNodeInfo(const char *path, struct node *root, struct node **node);

int GetNodeInfo(const char *path, struct node *root, struct node **node) 
{
  if(!S_ISDIR(root->vstat.st_mode)) {
    errno = ENOTDIR;
    return 0;
  }

  if(path[0] != '/') {
    errno = EINVAL;
    return 0;
  }

  if(path[1] == '\0') {
    *node = root;
    return 1;
  }

  // Extract name from path
  const char *name = path + 1;
  int namelen = 0;
  const char *name_end = name;
  while(*name_end != '\0' && *name_end != '/') {
    name_end++;
    namelen++;
  }

  // Search directory
  struct direntry *dirent;
  if(!FindDir(root, name, namelen, &dirent)) {
    errno = ENOENT;
    return 0;
  }

  if(*name_end == '\0') {
    // Last node in path
    *node = dirent->node;
    return 1;
  } else {
    // Not the last node in path (or a trailing slash)
    return GetNodeInfo(name_end, dirent->node, node);
  }
}

int AddDir(struct node *dirnode, struct direntry *entry, int replace, int *added) 
{
  struct direntry **dir = (struct direntry **) &dirnode->data;
  struct direntry *existing_entry;

  if(FindDir(dirnode, entry->name, strlen(entry->name), &existing_entry)) {
    if(replace) {
      *added = 0;
      existing_entry->node = entry->node;
      return 1;
    } else {
      errno = EEXIST;
      return 0;
    }
  }

  *added = 1;

  if(*dir == NULL) {
    *dir = entry;
    entry->next = NULL;
  } else {
    entry->next = *dir;
    *dir = entry;
  }

  // The entry is now linked in the directory
  entry->node->vstat.st_nlink++;

  // If the entry is a directory, .. is an implicit hardlink to the parent
  // directory.
  if(S_ISDIR(entry->node->vstat.st_mode)) {
    dirnode->vstat.st_nlink++;
  }

  return 1;
}

int DirAlloc(struct node *dirnode, const char *name, struct node *node, int replace) 
{
  struct direntry *entry = malloc(sizeof(struct direntry));
  int added;

  if(!entry) {
    errno = ENOMEM;
    return 0;
  }

  strcpy(entry->name, name);
  entry->node = node;

  if(!AddDir(dirnode, entry, replace, &added)) {
    free(entry);
    return 0;
  }

  if(!added) free(entry);

  return 1;
}

int RemoveDir(struct node *dirnode, const char *name) 
{
  struct direntry **dir = (struct direntry **) &dirnode->data;

  struct direntry *ent = *dir;
  struct direntry **ptr = dir;

  while(ent != NULL) {
    if(strcmp(ent->name, name) == 0) {
      *ptr = ent->next;

      // See AddDir for details
      if(S_ISDIR(ent->node->vstat.st_mode)) {
        dirnode->vstat.st_nlink--;
      }

      free(ent);

      return 1;
    }

    ptr = &ent->next;
    ent = ent->next;
  }

  errno = ENOENT;

  return 0;
}

int FindDir(struct node *dirnode, const char *name, int namelen, struct direntry **entry) 
{
  struct direntry *ent = (struct direntry *) dirnode->data;

  while(ent != NULL) {
    if(strlen(ent->name) == namelen) {
      if(strncmp(ent->name, name, namelen) == 0) {
        if(entry != NULL) *entry = ent;
        return 1;
      }
    }
    ent = ent->next;
  }

  errno = ENOENT;

  return 0;
}


char * DirnameSafe(const char *msg) {
  char *buf = strdup(msg);
  char *dir = dirname(buf);
  char *res = strdup(dir);
  free(buf);
  return res;
}

char * BaseNameSafe(const char *msg) {
  char *buf = strdup(msg);
  char *nam = basename(buf);
  char *res = strdup(nam);
  free(buf);
  return res;
}

int getnodebypath(const char *path, struct filesystem *fs, struct node **node) {
  return GetNodeInfo(path, fs->root, node);
}

static void UpdateTime(struct node *node, int which) {
  time_t now = time(0);
  if(which & U_ATIME) node->vstat.st_atime = now;
  if(which & U_CTIME) node->vstat.st_ctime = now;
  if(which & U_MTIME) node->vstat.st_mtime = now;
}

static int INITSTAT(struct node *node, mode_t mode) {
  struct stat *stbuf = &node->vstat;
  memset(stbuf, 0, sizeof(struct stat));
  stbuf->st_mode  = mode;
  stbuf->st_nlink = 0;
  UpdateTime(node, U_ATIME | U_MTIME | U_CTIME);
  return 1;
}

static int createentry(const char *path, mode_t mode, struct node **node) {
  char *dirpath = DirnameSafe(path);

  // Find parent node
  struct node *dir;
  int ret = getnodebypath(dirpath, &the_fs, &dir);
  free(dirpath);
  if(!ret) {
    return -errno;
  }

  // Create new node
  *node = malloc(sizeof(struct node));
  if(!*node) {
    return -ENOMEM;
  }

  (*node)->fd_count = 0;
  (*node)->delete_on_close = 0;

  // Initialize stats
  if(!INITSTAT(*node, mode)) {
    free(*node);
    return -errno;
  }

  struct fuse_context *ctx = fuse_get_context();
  (*node)->vstat.st_uid = ctx->uid;
  (*node)->vstat.st_gid = ctx->gid;

  // Add to parent directory
  if(!DirAlloc(dir, BaseNameSafe(path), *node, 0)) {
    free(*node);
    return -errno;
  }

  return 0;
}


//
// Filesystem entry points
//

static int memfs_getattr(const char *path, struct stat *stbuf) {
  struct node *node;
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  stbuf->st_mode   = node->vstat.st_mode;
  stbuf->st_nlink  = node->vstat.st_nlink;
  stbuf->st_size   = node->vstat.st_size;
  stbuf->st_blocks = node->vstat.st_blocks;
  stbuf->st_uid    = node->vstat.st_uid;
  stbuf->st_gid    = node->vstat.st_gid;
  stbuf->st_mtime  = node->vstat.st_mtime;
  stbuf->st_atime  = node->vstat.st_atime;
  stbuf->st_ctime  = node->vstat.st_ctime;

  // Directories contain the implicit hardlink '.'
  if(S_ISDIR(node->vstat.st_mode)) {
    stbuf->st_nlink++;
  }

  return 0;
}

static int memfs_readlink(const char *path, char *buf, size_t size) {
  struct node *node;
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  if(!S_ISLNK(node->vstat.st_mode)) {
    return -ENOLINK;
  }

  if(node->vstat.st_size > size) {
    memcpy(buf, node->data, size);
  } else {
    strcpy(buf, node->data);
  }

  return 0;
}

static int memfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
  struct node *dir;
  if(!getnodebypath(path, &the_fs, &dir)) {
    return -errno;
  }

  if(!S_ISDIR(dir->vstat.st_mode)) {
    return -ENOTDIR;
  }

  filler(buf, ".",  &dir->vstat, 0);
  if(dir == the_fs.root) {
    filler(buf, "..", NULL, 0);
  } else {
    char *parent_path = DirnameSafe(path);
    struct node *parent;
    getnodebypath(parent_path, &the_fs, &parent);
    free(parent_path);
    filler(buf, "..", &parent->vstat, 0);
  }

  struct direntry *entry = dir->data;
  while(entry != NULL) {
    if(filler(buf, entry->name, &entry->node->vstat, 0))
      break;
    entry = entry->next;
  }

  return 0;
}

static int memfs_mknod(const char *path, mode_t mode, dev_t rdev) {
  struct node *node;
  int res = createentry(path, mode, &node);
  if(res) return res;

  if(S_ISREG(mode)) {
    node->data = NULL;
    node->vstat.st_blocks = 0;
  } else {
    return -ENOSYS;
  }

  return 0;
}

static int memfs_mkdir(const char *path, mode_t mode) {
  struct node *node;
  int res = createentry(path, S_IFDIR | mode, &node);
  if(res) return res;

  // No entries
  node->data = NULL;

  return 0;
}

static int memfs_unlink(const char *path) {
  char *dirpath, *name;
  struct node *dir, *node;

  // Find inode
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  if(S_ISDIR(node->vstat.st_mode)) {
    return -EISDIR;
  }

  dirpath = DirnameSafe(path);

  // Find parent inode
  if(!getnodebypath(dirpath, &the_fs, &dir)) {
    free(dirpath);
    return -errno;
  }

  free(dirpath);

  name = BaseNameSafe(path);

  // Find directory entry in parent
  if(!RemoveDir(dir, name)) {
    free(name);
    return -errno;
  }

  free(name);

  // If the link count is zero, delete the associated data
  if(node->vstat.st_nlink == 0) {
    if(node->fd_count == 0) {
      // No open file descriptors, we can safely delete the node
      if(node->data) free(node->data);
      free(node);
    } else {
      // There are open file descriptors, schedule deletion
      node->delete_on_close = 1;
    }
  }

  return 0;
}

static int memfs_rmdir(const char *path) {
  char *dirpath, *name;
  struct node *dir, *node;

  // Find inode
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  if(!S_ISDIR(node->vstat.st_mode)) {
    return -ENOTDIR;
  }

  // Check if directory is empty
  if(node->data != NULL) {
    return -ENOTEMPTY;
  }

  dirpath = DirnameSafe(path);

  // Find parent inode
  if(!getnodebypath(dirpath, &the_fs, &dir)) {
    free(dirpath);
    return -errno;
  }

  free(dirpath);

  name = BaseNameSafe(path);

  // Find directory entry in parent
  if(!RemoveDir(dir, name)) {
    free(name);
    return -errno;
  }

  free(name);

  free(node);

  return 0;
}

static int memfs_symlink(const char *from, const char *to) {
  struct node *node;
  int res = createentry(to, S_IFLNK | 0766, &node);
  if(res) return res;

  node->data = strdup(from);
  node->vstat.st_size = strlen(from);

  return 0;
}

// TODO: Adapt to description: https://linux.die.net/man/2/rename
static int memfs_rename(const char *from, const char *to) {
  char *fromdir, *fromnam, *todir, *tonam;
  struct node *node, *fromdirnode, *todirnode;

  if(!getnodebypath(from, &the_fs, &node)) {
    return -errno;
  }

  fromdir = DirnameSafe(from);

  if(!getnodebypath(fromdir, &the_fs, &fromdirnode)) {
    free(fromdir);
    return -errno;
  }

  free(fromdir);

  todir = DirnameSafe(to);

  if(!getnodebypath(todir, &the_fs, &todirnode)) {
    free(todir);
    return -errno;
  }

  free(todir);

  tonam = BaseNameSafe(to);

  // TODO: When replacing, perform the same things as when unlinking
  if(!DirAlloc(todirnode, tonam, node, 1)) {
    free(tonam);
    return -errno;
  }

  free(tonam);

  fromnam = BaseNameSafe(from);

  if(!RemoveDir(fromdirnode, fromnam)) {
    free(fromnam);
    return -errno;
  }

  free(fromnam);

  return 0;
}

static int memfs_link(const char *from, const char *to) {
  char *todir, *tonam;
  struct node *node, *todirnode;

  if(!getnodebypath(from, &the_fs, &node)) {
    return -errno;
  }

  todir = DirnameSafe(to);

  if(!getnodebypath(todir, &the_fs, &todirnode)) {
    free(todir);
    return -errno;
  }

  free(todir);

  tonam = BaseNameSafe(to);

  if(!DirAlloc(todirnode, tonam, node, 0)) {
    free(tonam);
    return -errno;
  }

  free(tonam);

  return 0;
}

static int memfs_chmod(const char *path, mode_t mode) {
  struct node *node;
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  mode_t mask = S_ISUID | S_ISGID | S_ISVTX |
                S_IRUSR | S_IWUSR | S_IXUSR |
                S_IRGRP | S_IWGRP | S_IXGRP |
                S_IROTH | S_IWOTH | S_IXOTH;

  node->vstat.st_mode = (node->vstat.st_mode & ~mask) | (mode & mask);

  UpdateTime(node, U_CTIME);

  return 0;
}

static int memfs_chown(const char *path, uid_t uid, gid_t gid) {
  struct node *node;
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  node->vstat.st_uid = uid;
  node->vstat.st_gid = gid;

  UpdateTime(node, U_CTIME);

  return 0;
}

static int memfs_utimens(const char *path, const struct timespec ts[2]) {
  struct node *node;
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  node->vstat.st_atime = ts[0].tv_sec;
  node->vstat.st_mtime = ts[1].tv_sec;

  return 0;
}

static int memfs_truncate(const char *path, off_t size) {
  struct node *node;
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  // Calculate new block count
  blkcnt_t newblkcnt = (size + BLOCKSIZE - 1) / BLOCKSIZE;
  blkcnt_t oldblkcnt = node->vstat.st_blocks;

  if(oldblkcnt < newblkcnt) {
    // Allocate additional memory
    void *newdata = malloc(newblkcnt * BLOCKSIZE);
    if(!newdata) {
      return -ENOMEM;
    }

    memcpy(newdata, node->data, node->vstat.st_size);
    free(node->data);
    node->data = newdata;
  } else if(oldblkcnt > newblkcnt) {
    // Allocate new memory so we can free the unnecessarily large memory
    void *newdata = malloc(newblkcnt * BLOCKSIZE);
    if(!newdata) {
      return -ENOMEM;
    }

    memcpy(newdata, node->data, size);
    free(node->data);
    node->data = newdata;
  }

  // Fill additional memory with zeroes
  if(node->vstat.st_size < size) {
    memset(node->data + node->vstat.st_size, 0, node->vstat.st_size - size);
  }

  // Update file size
  node->vstat.st_size = size;
  node->vstat.st_blocks = newblkcnt;

  return 0;
}

static int memfs_open(const char *path, struct fuse_file_info *fi) {
  struct node *node;
  if(!getnodebypath(path, &the_fs, &node)) {
    return -errno;
  }

  if(!S_ISREG(node->vstat.st_mode)) {
    if(S_ISDIR(node->vstat.st_mode)) {
      return -EISDIR;
    }
  }

  // Update file timestamps
  UpdateTime(node, U_ATIME);

  // The "file handle" is a pointer to a struct we use to keep track of the inode and the
  // flags passed to open().
  struct filehandle *fh = malloc(sizeof(struct filehandle));
  fh->node    = node;
  fh->o_flags = fi->flags;

  fi->fh = (uint64_t) fh;

  node->fd_count++;

  return 0;
}

static int memfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
  struct filehandle *fh = (struct filehandle *) fi->fh;

  // Check whether the file was opened for reading
  if(!O_READ(fh->o_flags)) {
    return -EACCES;
  }

  struct node *node = fh->node;

  off_t filesize = node->vstat.st_size;

  // Check whether offset is at or beyond the end of file
  if(offset >= filesize) {
    return 0;
  }

  // Calculate number of bytes to copy
  size_t avail = filesize - offset;
  size_t n = (size < avail) ? size : avail;

  // Copy file contents
  memcpy(buf, node->data + offset, n);

  UpdateTime(node, U_ATIME);

  return n;
}

static int memfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
  struct filehandle *fh = (struct filehandle *) fi->fh;

  // Check whether the file was opened for writing
  if(!O_WRITE(fh->o_flags)) {
    return -EACCES;
  }

  struct node *node = fh->node;

  // Calculate number of required blocks
  blkcnt_t req_blocks = (offset + size + BLOCKSIZE - 1) / BLOCKSIZE;

  if(node->vstat.st_blocks < req_blocks) {
    // Allocate more memory
    void *newdata = malloc(req_blocks * BLOCKSIZE);
    if(!newdata) {
      return -ENOMEM;
    }

    // Copy old contents
    if(node->data != NULL) {
      memcpy(newdata, node->data, node->vstat.st_size);
      free(node->data);
    }

    // Update allocation information
    node->data = newdata;
    node->vstat.st_blocks = req_blocks;
  }

  // Write to file buffer
  memcpy(((char *) node->data) + offset, buf, size);

  // Update file size if necessary
  off_t minsize = offset + size;
  if(minsize > node->vstat.st_size) {
    node->vstat.st_size = minsize;
  }

  UpdateTime(node, U_CTIME | U_MTIME);

  return size;
}

static int memfs_release(const char *path, struct fuse_file_info *fi) {
  struct filehandle *fh = (struct filehandle *) fi->fh;

  if(--fh->node->fd_count == 0) {
    if(fh->node->delete_on_close) {
      if(fh->node->data) free(fh->node->data);
      free(fh->node);
    }
  }

  free(fh);

  return 0;
}

static struct fuse_operations memfs_oper = {
  .getattr      = memfs_getattr,
  .readlink     = memfs_readlink,
  .readdir      = memfs_readdir,
  .mknod        = memfs_mknod,
  .mkdir        = memfs_mkdir,
  .symlink      = memfs_symlink,
  .unlink       = memfs_unlink,
  .rmdir        = memfs_rmdir,
  .rename       = memfs_rename,
  .link         = memfs_link,
  .chmod        = memfs_chmod,
  .chown        = memfs_chown,
  .truncate     = memfs_truncate,
  .utimens      = memfs_utimens,
  .open         = memfs_open,
  .read         = memfs_read,
  .write        = memfs_write,
  .release      = memfs_release
};


int main(int argc, char *argv[]) {
  // Initialize root directory
  struct node *root = malloc(sizeof(struct node));

  memset(root, 0, sizeof(struct node));
  INITSTAT(root, S_IFDIR | 0755);
  root->vstat.st_uid = getuid();
  root->vstat.st_gid = getgid();

  // No entries
  root->data = NULL;

  // Set root directory of filesystem
  the_fs.root = root;

  umask(0);

  return fuse_main(argc, argv, &memfs_oper, NULL);
}

