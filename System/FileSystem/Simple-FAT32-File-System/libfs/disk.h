#ifndef _DISK_H
#define _DISK_H

#include <stddef.h>

// 块大小
#define BLOCK_SIZE 4096

int block_disk_open(const char *diskname);
int block_disk_close(void);
int block_disk_count(void);
int block_write(size_t block, const void *buf);
int block_read(size_t block, void *buf);

#endif /* _DISK_H */

