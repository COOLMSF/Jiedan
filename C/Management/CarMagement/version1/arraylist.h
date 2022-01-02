#ifndef ALGORITHM_ARRAYLIST_H
#define ALGORITHM_ARRAYLIST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void *ArrayListValue;

typedef struct _ArrayList ArrayList;

struct _ArrayList {


	ArrayListValue *data;


	unsigned int length;


	unsigned int _alloced;
};


typedef int (*ArrayListEqualFunc)(ArrayListValue value1,
                                  ArrayListValue value2);

typedef int (*ArrayListCompareFunc)(ArrayListValue value1,
                                    ArrayListValue value2);

ArrayList *arraylist_new(unsigned int length);


void arraylist_free(ArrayList *arraylist);


int arraylist_append(ArrayList *arraylist, ArrayListValue data);


int arraylist_prepend(ArrayList *arraylist, ArrayListValue data);


void arraylist_remove(ArrayList *arraylist, unsigned int index);


void arraylist_remove_range(ArrayList *arraylist, unsigned int index,
                            unsigned int length);


int arraylist_insert(ArrayList *arraylist, unsigned int index,
                     ArrayListValue data);

void arraylist_sort(ArrayList *arraylist, ArrayListCompareFunc compare_func);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ALGORITHM_ARRAYLIST_H */

