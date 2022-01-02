#include <stdio.h>
#include "slist.h"

int main()
{
    SListEntry *entry;
    int a = 0x11, b = 0x22, c = 0x33;

    slist_append(&entry, (SListValue*) &a);
    slist_append(&entry, (SListValue*) &b);
    slist_append(&entry, (SListValue*) &c);

    SListEntry *p = entry;
    while (p != NULL) {
        SListValue value = slist_data(p);
        printf("%x ", *(int *)value);
        p = slist_next(p);
    }

    // SlistEntry *p = entry;
    // for (int i = 0; i < 3; i++) {
    //     printf("%x ", *(int *)slist_data(entry));
    //     p = slist_next()
    // }

}
