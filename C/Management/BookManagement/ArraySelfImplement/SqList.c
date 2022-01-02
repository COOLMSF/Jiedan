#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include "SqList.h"

SqEntry *sqlist_init(size_t n_element)
{
    SqEntry *entry;
    /*
     * 16 elements for default
     */
    if (n_element < 16)
        n_element = 16;

    entry = malloc(sizeof(SqEntry));
    if (entry == NULL)
        return SQENTRY_NULL;

    entry->value = malloc(sizeof(SqValue) * n_element);
    if (entry->value == NULL)
        return SQVALUE_NULL;
    entry->n_element = n_element;

    return entry;
}

int sqlist_enlarge(SqEntry *entry)
{
    SqValue *data;
    /*
     * Enlarge double size
     */
    size_t n_new_element = entry->n_element * 2;

    /*
     * realloc memory
     */
    data = realloc(entry->value, n_new_element * sizeof(SqValue));
    if (data == NULL)
        return -1;

    /*
     * update data
     */
    entry->value = data;
    entry->n_element = n_new_element;

    return 1;
}

int sqlist_insert(SqEntry *entry, SqValue value, size_t index)
{
    /*
     * There are two suitation,
     * 1. entry is SQENTRY_NULL, which should return -1.
     * 2. otherwise, malloc memory and insert it
     */
    if (index > entry->n_used)
        return -1;

    if (entry == SQENTRY_NULL)
        return -1;

    /*
     * if memory is not enough, enlarge it
     */
    if (entry->n_used + 1 > entry->n_element)
        if (!sqlist_enlarge(entry))
            return -1;

    /*
     * inserting should malloc new memory and use memcpy to copy
     * from index to the end of sqlist entry
     */
    memmove(entry->value[index + 1], entry->value[index], (entry->n_element - index) * sizeof(SqEntry));
    entry->value[index] = value;
    entry->n_used++;

    return 1;
}

int sqlist_delete_by_value(SqEntry *entry, SqValue value)
{
}

int sqlist_delete_by_index(SqEntry *entry, size_t index)
{
    if (entry == SQENTRY_NULL)
        return -1;

    if (entry->n_used < 0)
        return -1;
    /*
     * move backwards
     */
    memmove(&entry->value[index], &entry->value[index + 1], sizeof(entry->n_element - index + 1) * sizeof(SqEntry));
    entry->n_used--;

    return 1;
}

SqValue sqlist_query(SqEntry *entry, SqValue value, SqListComapreFunc compare_func)
{
    /*
     * Use callback function to maxmium the portablity
     */
    for (size_t i = 0; i < entry->n_element; i++) {
        // if the value is NULL, skip it
        if (entry->value[i] == NULL)
            continue;
        if (compare_func(entry->value[i], value))
            return entry->value[i];
    }
    return SQVALUE_ERR;
}

int sqlist_modify(SqEntry *entry, SqValue old_value, SqValue new_value)
{
    for (size_t i = 0; i < entry->n_used; i++)
        if (memcmp(entry->value[i], (void *)old_value, sizeof(SqValue)) == 0)
            entry->value[i] = new_value;

    return -1;
}

int sqlist_free(SqEntry *entry)
{
    free(entry->value);
    return 1;
}

int sqlist_append(SqEntry *entry, SqValue value)
{
    if (sqlist_insert(entry, value, entry->n_used) == -1)
        return -1;
    return 1;
}

int sqlist_prepend(SqEntry *entry, SqValue value)
{
    if (sqlist_insert(entry, value, 0) == -1)
        return -1;
    return 1;
}
