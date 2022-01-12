#include <stdlib.h>
#include <string.h>

#include "arraylist.h"

ArrayList *arraylist_new(unsigned int length)
{
	ArrayList *new_arraylist;


	if (length <= 0) {
		length = 16;
	}

	new_arraylist = (ArrayList *) malloc(sizeof(ArrayList));

	if (new_arraylist == NULL) {
		return NULL;
	}

	new_arraylist->_alloced = length;
	new_arraylist->length = 0;

	new_arraylist->data = malloc(length * sizeof(ArrayListValue));

	if (new_arraylist->data == NULL) {
		free(new_arraylist);
		return NULL;
	}

	return new_arraylist;
}

void arraylist_free(ArrayList *arraylist)
{

	if (arraylist != NULL) {
		free(arraylist->data);
		free(arraylist);
	}
}

static int arraylist_enlarge(ArrayList *arraylist)
{
	ArrayListValue *data;
	unsigned int newsize;


	newsize = arraylist->_alloced * 2;


	data = realloc(arraylist->data, sizeof(ArrayListValue) * newsize);

	if (data == NULL) {
		return 0;
	} else {
		arraylist->data = data;
		arraylist->_alloced = newsize;

		return 1;
	}
}

int arraylist_insert(ArrayList *arraylist, unsigned int index,
                     ArrayListValue data)
{
	/* Sanity check the index */

	if (index > arraylist->length) {
		return 0;
	}

	/* Increase the size if necessary */

	if (arraylist->length + 1 > arraylist->_alloced) {
		if (!arraylist_enlarge(arraylist)) {
			return 0;
		}
	}

	/* Move the contents of the array forward from the index
	 * onwards */

	memmove(&arraylist->data[index + 1],
	        &arraylist->data[index],
	        (arraylist->length - index) * sizeof(ArrayListValue));

	/* Insert the new entry at the index */

	arraylist->data[index] = data;
	++arraylist->length;

	return 1;
}

int arraylist_append(ArrayList *arraylist, ArrayListValue data)
{
	return arraylist_insert(arraylist, arraylist->length, data);
}

void arraylist_remove_range(ArrayList *arraylist, unsigned int index,
                            unsigned int length)
{

	if (index > arraylist->length || index + length > arraylist->length) {
		return;
	}

	memmove(&arraylist->data[index],
	        &arraylist->data[index + length],
	        (arraylist->length - (index + length))
	            * sizeof(ArrayListValue));

	/* Decrease the counter */

	arraylist->length -= length;
}

void arraylist_remove(ArrayList *arraylist, unsigned int index)
{
	arraylist_remove_range(arraylist, index, 1);
}
