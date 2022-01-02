#include <stdio.h>
#include <stdlib.h>

typedef void *SListValue;

typedef struct _SListEntry NodeT;
struct _SListEntry {
	SListValue data;
	NodeT *next;
};

void _free(NodeT *list)
{
	NodeT *entry;

	/* Iterate over each entry, freeing each list entry, until the
	 * end is reached */

	entry = list;

	while (entry != NULL) {
		NodeT *next;

		next = entry->next;

		_free(entry);

		entry = next;
	}
}

void showLL(NodeT *list)
{
    NodeT *p;

    for (p = list; p != NULL; p++) {
        printf("%d ", *(int *)p->data);
    }
}

NodeT *slist_append(NodeT *list, SListValue *data)
{
	NodeT *rover;
	NodeT *newentry;

	/* Create new list entry */

	newentry = malloc(sizeof(NodeT));

	if (newentry == NULL) {
		return NULL;
	}

	newentry->data = data;
	newentry->next = NULL;

	/* Hooking into the list is different if the list is empty */

	if (list == NULL) {

		/* Create the start of the list */

		list = newentry;

	} else {

		/* Find the end of list */

		for (rover=list; rover->next != NULL; rover = rover->next);

		/* Add to the end of list */

		rover->next = newentry;
	}

	return newentry;
}


int main(int argc, char const* argv[])
{
    NodeT *node;

    int a = 100;

    slist_append(node, (SListValue *)&a);
    showLL(node);
}
