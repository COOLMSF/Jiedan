#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNAME 254
#define MAXBUF 1024
#define MAXBOOK 100

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

struct _EmpInfo {
    int id;
    char name[MAXNAME];
    char gender[MAXNAME];
    char join_date[MAXNAME];
    // 文化程度
    int level;
    double age;
    double salary;
};
typedef struct _EmpInfo EmpInfo;

typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);


void slist_free(SListEntry *list)
{
	SListEntry *entry;

	/* Iterate over each entry, freeing each list entry, until the
	 * end is reached */

	entry = list;

	while (entry != NULL) {
		SListEntry *next;

		next = entry->next;

		free(entry);

		entry = next;
	}
}

SListEntry *slist_prepend(SListEntry **list, SListValue data)
{
	SListEntry *newentry;

	/* Create new entry */

	newentry = malloc(sizeof(SListEntry));

	if (newentry == NULL) {
		return NULL;
	}

	newentry->data = data;

	/* Hook into the list start */

	newentry->next = *list;
	*list = newentry;

	return newentry;
}

SListEntry *slist_append(SListEntry **list, SListValue data)
{
	SListEntry *rover;
	SListEntry *newentry;

	/* Create new list entry */

	newentry = malloc(sizeof(SListEntry));

	if (newentry == NULL) {
		return NULL;
	}

	newentry->data = data;
	newentry->next = NULL;

	/* Hooking into the list is different if the list is empty */

	if (*list == NULL) {

		/* Create the start of the list */

		*list = newentry;

	} else {

		/* Find the end of list */

		for (rover=*list; rover->next != NULL; rover = rover->next);

		/* Add to the end of list */

		rover->next = newentry;
	}

	return newentry;
}

SListValue slist_data(SListEntry *listentry)
{
	return listentry->data;
}

void slist_set_data(SListEntry *listentry, SListValue data)
{
	if (listentry != NULL) {
		listentry->data = data;
	}
}

SListEntry *slist_next(SListEntry *listentry)
{
	return listentry->next;
}

SListEntry *slist_nth_entry(SListEntry *list, unsigned int n)
{
	SListEntry *entry;
	unsigned int i;

	entry = list;

	for (i=0; i<n; ++i) {

		if (entry == NULL) {
			return NULL;
		}
		entry = entry->next;
	}

	return entry;
}

SListValue slist_nth_data(SListEntry *list, unsigned int n)
{
	SListEntry *entry;

	/* Find the specified entry */

	entry = slist_nth_entry(list, n);

	/* If out of range, return NULL, otherwise return the data */

	if (entry == NULL) {
		return SLIST_NULL;
	} else {
		return entry->data;
	}
}

unsigned int slist_length(SListEntry *list)
{
	SListEntry *entry;
	unsigned int length;

	length = 0;
	entry = list;

	while (entry != NULL) {

		/* Count the number of entries */

		++length;

		entry = entry->next;
	}

	return length;
}

SListValue *slist_to_array(SListEntry *list)
{
	SListEntry *rover;
	SListValue *array;
	unsigned int length;
	unsigned int i;

	/* Allocate an array equal in size to the list length */

	length = slist_length(list);

	array = malloc(sizeof(SListValue) * length);

	if (array == NULL) {
		return NULL;
	}

	/* Add all entries to the array */

	rover = list;

	for (i=0; i<length; ++i) {

		/* Add this node's data */

		array[i] = rover->data;

		/* Jump to the next list node */

		rover = rover->next;
	}

	return array;
}

int slist_remove_entry(SListEntry **list, SListEntry *entry)
{
	SListEntry *rover;

	/* If the list is empty, or entry is NULL, always fail */

	if (*list == NULL || entry == NULL) {
		return 0;
	}

	/* Action to take is different if the entry is the first in the list */

	if (*list == entry) {

		/* Unlink the first entry and update the starting pointer */

		*list = entry->next;

	} else {

		/* Search through the list to find the preceding entry */

		rover = *list;

		while (rover != NULL && rover->next != entry) {
			rover = rover->next;
		}

		if (rover == NULL) {

			/* Not found in list */

			return 0;

		} else {

			/* rover->next now points at entry, so rover is the
			 * preceding entry. Unlink the entry from the list. */

			rover->next = entry->next;
		}
	}

	/* Free the list entry */

	free(entry);

	/* Operation successful */

	return 1;
}

unsigned int slist_remove_data(SListEntry **list, SListEqualFunc callback,
                               SListValue data)
{
	SListEntry **rover;
	SListEntry *next;
	unsigned int entries_removed;

	entries_removed = 0;

	/* Iterate over the list.  'rover' points at the entrypoint into the
	 * current entry, ie. the list variable for the first entry in the
	 * list, or the "next" field of the preceding entry. */

	rover = list;

	while (*rover != NULL) {

		/* Should this entry be removed? */

		if (callback((*rover)->data, data) != 0) {

			/* Data found, so remove this entry and free */

			next = (*rover)->next;
			free(*rover);
			*rover = next;

			/* Count the number of entries removed */

			++entries_removed;
		} else {

			/* Advance to the next entry */

			rover = &((*rover)->next);
		}
	}

	return entries_removed;
}

/* Function used internally for sorting.  Returns the last entry in the
 * new sorted list */

static SListEntry *slist_sort_internal(SListEntry **list,
                                       SListCompareFunc compare_func)
{
	SListEntry *pivot;
	SListEntry *rover;
	SListEntry *less_list, *more_list;
	SListEntry *less_list_end, *more_list_end;

	/* If there are less than two entries in this list, it is
	 * already sorted */

	if (*list == NULL || (*list)->next == NULL) {
		return *list;
	}

	/* The first entry is the pivot */

	pivot = *list;

	/* Iterate over the list, starting from the second entry.  Sort
	 * all entries into the less and more lists based on comparisons
	 * with the pivot */

	less_list = NULL;
	more_list = NULL;
	rover = (*list)->next;

	while (rover != NULL) {
		SListEntry *next = rover->next;

		if (compare_func(rover->data, pivot->data) < 0) {

			/* Place this in the less list */

			rover->next = less_list;
			less_list = rover;

		} else {

			/* Place this in the more list */

			rover->next = more_list;
			more_list = rover;

		}

		rover = next;
	}

	/* Sort the sublists recursively */

	less_list_end = slist_sort_internal(&less_list, compare_func);
	more_list_end = slist_sort_internal(&more_list, compare_func);

	/* Create the new list starting from the less list */

	*list = less_list;

	/* Append the pivot to the end of the less list.  If the less list
	 * was empty, start from the pivot */

	if (less_list == NULL) {
		*list = pivot;
	} else {
		less_list_end->next = pivot;
	}

	/* Append the more list after the pivot */

	pivot->next = more_list;

	/* Work out what the last entry in the list is.  If the more list was
	 * empty, the pivot was the last entry.  Otherwise, the end of the
	 * more list is the end of the total list. */

	if (more_list == NULL) {
		return pivot;
	} else {
		return more_list_end;
	}
}

void slist_sort(SListEntry **list, SListCompareFunc compare_func)
{
	slist_sort_internal(list, compare_func);
}

SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data)
{
	SListEntry *rover;

	/* Iterate over entries in the list until the data is found */

	for (rover=list; rover != NULL; rover=rover->next) {
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	/* Not found */

	return NULL;
}

void slist_iterate(SListEntry **list, SListIterator *iter)
{
	/* Start iterating from the beginning of the list. */

	iter->prev_next = list;

	/* We have not yet read the first item. */

	iter->current = NULL;
}

int slist_iter_has_more(SListIterator *iter)
{
	if (iter->current == NULL || iter->current != *iter->prev_next) {

		/* Either we have not read the first entry, the current
		 * item was removed or we have reached the end of the
		 * list.  Use prev_next to determine if we have a next
		 * value to iterate over. */

		return *iter->prev_next != NULL;

	} else {

		/* The current entry has not been deleted.  There
		 * is a next entry if current->next is not NULL. */

		return iter->current->next != NULL;
	}
}

SListValue slist_iter_next(SListIterator *iter)
{
	if (iter->current == NULL || iter->current != *iter->prev_next) {

		/* Either we are reading the first entry, we have reached
		 * the end of the list, or the previous entry was removed.
		 * Get the next entry with iter->prev_next. */

		iter->current = *iter->prev_next;

	} else {

		/* Last value returned from slist_iter_next was not
		 * deleted. Advance to the next entry. */

		iter->prev_next = &iter->current->next;
		iter->current = iter->current->next;
	}

	/* Have we reached the end of the list? */

	if (iter->current == NULL) {
		return SLIST_NULL;
	} else {
		return iter->current->data;
	}
}

void slist_iter_remove(SListIterator *iter)
{
	if (iter->current == NULL || iter->current != *iter->prev_next) {

		/* Either we have not yet read the first item, we have
		 * reached the end of the list, or we have already removed
		 * the current value.  Either way, do nothing. */

	} else {

		/* Remove the current entry */

		*iter->prev_next = iter->current->next;
		free(iter->current);
		iter->current = NULL;
	}
}

int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _EmpInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

int show_info(SListEntry **list)
{
    SListValue *value;
    SListEntry *p = *list;

    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int n = 0;
    double sum_salary = 0.0;
    double sum_age = 0.0;
    int cnt_daxue = 0;
    int cnt_zhongxue = 0;
    int cnt_xiaoxue = 0;

    while (p != NULL) {
        value = p->data;
        sum_salary += ((struct _EmpInfo *) value)->salary;
        sum_age += ((struct _EmpInfo *) value)->age;

        if ((((struct _EmpInfo *) value)->level) == 1) {
            cnt_daxue++;
        } else if ((((struct _EmpInfo *) value)->level) == 2) {
            cnt_zhongxue++;
        } else {
            cnt_xiaoxue++;
        }

        p = p->next;
        n++;
    }

    printf("平均年龄:%lf\n", 1.0 * sum_age / n);
    printf("平均工资:%lf\n", 1.0 * sum_salary / n);
    printf("大学文化占:%lf\n", 1.0 * cnt_daxue / n);
    printf("中学文化占:%lf\n", 1.0 * cnt_zhongxue / n);
    printf("小学文化占:%lf\n", 1.0 * cnt_xiaoxue / n);

}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用职工管理系统");
    puts("1:) 添加职工信息");
    puts("2:) 输出信息");
    puts("3:) 退出");
    puts("-------------------");
    puts("");
}

int insert_emp(SListEntry **list)
{
    EmpInfo *emp_info;
    SListEntry *p;

    emp_info = malloc(sizeof (struct _EmpInfo));
    if (emp_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入职工id:");
    scanf("%d", &emp_info->id);
    puts("输入职工名字:");
    scanf("%s", emp_info->name);
    puts("输入职工年龄:");
    scanf("%lf", &emp_info->age);
    puts("输入职工性别:");
    scanf("%s", emp_info->gender);
    puts("输入参加工作时间:");
    scanf("%s", emp_info->join_date);
    puts("输入文化程度(1: 大学 (2: 中学 (3: 小学");
    scanf("%d", &emp_info->level);
    puts("输入工资:");
    scanf("%lf", &emp_info->salary);
    puts("");

    if (slist_append(list, (SListValue *)emp_info) != NULL) {
        puts("----------------------");
        puts("插入职工成功");
        puts("----------------------");
        return 1;
    } else {
        puts("----------------------");
        puts("插入职工失败");
        puts("----------------------");
        return 0;
    }
}

int main(int argc, char const* argv[])
{
    int input;
    SListEntry *user_list = NULL;

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // user = ask_user_info();
                insert_emp(&user_list);
                break;
            case 2:
                show_info(&user_list);
                break;
            case 3:
                exit(EXIT_SUCCESS);
            default:
                puts("-------------------");
                puts("输入错误");
                puts("-------------------");
                break;
        }
    }
    return 0;
}

