#include <stdio.h>

#ifndef SQLIST_H
#define SQLIST_H

#define MAX_VALUE 1024

#define SQENTRY_NULL ((void *) 0)
#define SQVALUE_NULL ((void *) 0)
#define SQVALUE_ERR ((void *) -1)

// use void * to store any value
typedef void *SqValue;
typedef struct _SqEntry SqEntry;
typedef int (*SqListComapreFunc)(SqValue a, SqValue b);

struct _SqEntry {
    SqValue *value;
    size_t n_element;
    size_t n_used;
};

SqEntry *sqlist_init(size_t size);
int sqlist_insert(SqEntry *entry, SqValue value, size_t index);
int sqlist_enlarge(SqEntry *entry);
int sqlist_delete_by_index(SqEntry *entry, size_t index);
int sqlist_delete_by_value(SqEntry *entry, SqValue value);
SqValue sqlist_query(SqEntry *entry, SqValue value, SqListComapreFunc compare_func);
int sqlist_modify(SqEntry *entry, SqValue old_value, SqValue new_value);
int sqlist_free(SqEntry *entry);
int sqlist_append(SqEntry *entry, SqValue value);
int sqlist_prepend(SqEntry *entry, SqValue value);

#endif
