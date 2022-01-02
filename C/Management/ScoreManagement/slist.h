typedef void *SListValue;

typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};



typedef struct _SListIterator SListIterator;


struct _SListIterator {
	SListEntry **prev_next;
	SListEntry *current;
};

#define SLIST_NULL ((void *) 0)

typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);

typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);

void slist_free(SListEntry *list);


SListEntry *slist_append(SListEntry **list, SListValue data);
SListEntry *slist_next(SListEntry *listentry);
SListValue slist_data(SListEntry *listentry);

int slist_remove_entry(SListEntry **list, SListEntry *entry);
unsigned int slist_remove_data(SListEntry **list,
                               SListEqualFunc callback,
                               SListValue data);

SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data);

