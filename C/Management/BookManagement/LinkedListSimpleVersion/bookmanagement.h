#include <stdio.h>
#include "slist.h"

#define MAXNAME 254
#define MAXBUF 1024
#define MAXLINE 255
#define MAXBOOK 100

struct _BookInfo {
    int id;
    double price;
    char name[MAXNAME];
};
typedef struct _BookInfo BookInfo;

void welcome();
int insert_book(SListEntry **list);
int delete_book(SListEntry **list);
int delete_book_by_id(SListEntry **list, int id);
int modify_book(SListEntry **list);
int query_book(SListEntry **list);
int query_book_by_id(SListEntry **list, int id);
int callback_check_id(SListValue a, SListValue b);
void show_books(SListEntry *book_list);

int read_data_from_disk(FILE *fpr, SListEntry *book_list);
int write_data_to_disk(FILE *fpw, SListEntry *book_list);