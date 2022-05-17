#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>

#include "slist.h"

#define MAXNAME 254
#define MAXBUF 1024
#define MAXBOOK 100

struct _BookInfo {
    char id[4];
    char name[MAXNAME];
    char author_name[MAXNAME];
    enum { Novel, Classic, Tech } type;
    double price;
    int total_num;
    int left_num;
    // int borrow_time;
    // int return_time;
    // int max_borrow_time;
    // time_t borrowed_time;
};
typedef struct _BookInfo BookInfo;

struct _User {
    char id[4];
    int num_borrow;
    int max_num_borrow;
    char gender[MAXNAME];
    char name[MAXNAME];
    char username[MAXNAME];
    char passwd[MAXBUF];
    SListEntry *borrowed_book;
    enum { TEACHER, STUDENT } type;
};

void welcome();
void pre_welcome();

// user inspection

// login登陆成功，应该返回当前用户指针，否则返回NULL
struct _User *login(SListEntry **list);
int regist(SListEntry **list);
int forget_passwd(SListEntry **list);

int insert_book(SListEntry **list);
int delete_book(SListEntry **list);
int delete_book_by_id(SListEntry **list, int id);
int modify_book(SListEntry **list);
int query_book(SListEntry **list);
int query_book_by_id(SListEntry **list, char *id);
int callback_check_str_id(SListValue a, SListValue b);
int callback_check_id(SListValue a, SListValue b);
int callback_check_username(SListValue a, SListValue b);

int borrow_book(struct _User *user, SListEntry **book_list);
int return_book(struct _User *user,SListEntry **book_list);
int statistic(SListEntry *book_list);

// 初始化学生和教师可以借的书的数量和天数
void teacher_borrow(struct _BookInfo *p);
void student_borrow(struct _BookInfo *p);
struct _User *ask_user_info(struct _User *p);
int insert_user(SListEntry **list, SListValue *value);
void show_userinfo(struct _User *p);
void show_books(SListEntry *book_list);

// 信息存储
// 将用户信息存储到文件
int user_save_list_to_file(const char *filename, SListEntry *list);
// 从文件读取用户信息
int user_read_file_to_list(const char *filename, SListEntry **list);

// 同上
int book_save_list_to_file(const char *filename, SListEntry *list);
int book_read_file_to_list(const char *filename, SListEntry **list);

// 图书管理系统，作用与client_fd
int book_management();