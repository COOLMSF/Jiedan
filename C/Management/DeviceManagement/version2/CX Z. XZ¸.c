#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXBUF 1024

struct _DevInfo {
	int id;
	char deviceName[MAXBUF];
	char brandName[MAXBUF];
    char type[MAXBUF];
	double price;
	char buyTime[MAXBUF];
	char isFine[MAXBUF];
};

typedef void *SListValue;
typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};

#define SLIST_NULL ((void *) 0)
typedef struct _DevInfo DevInfo;
typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);

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

	if (*list == NULL) {
		*list = newentry;
	} else {
		for (rover=*list; rover->next != NULL; rover = rover->next);
		rover->next = newentry;
	}

	return newentry;
}

SListValue slist_data(SListEntry *listentry)
{
	return listentry->data;
}

int slist_remove_entry(SListEntry **list, SListEntry *entry)
{
	SListEntry *rover;

	if (*list == NULL || entry == NULL) {
		return 0;
	}

	if (*list == entry) {

		*list = entry->next;

	} else {

		rover = *list;

		while (rover != NULL && rover->next != entry) {
			rover = rover->next;
		}

		if (rover == NULL) {

			return 0;

		} else {

			rover->next = entry->next;
		}
	}

	free(entry);

	return 1;
}

unsigned int slist_remove_data(SListEntry **list, SListEqualFunc callback,
                               SListValue data)
{
	SListEntry **rover;
	SListEntry *next;
	unsigned int entries_removed;

	entries_removed = 0;

	rover = list;

	while (*rover != NULL) {


		if (callback((*rover)->data, data) != 0) {

			next = (*rover)->next;
			free(*rover);
			*rover = next;

			++entries_removed;
		} else {

			rover = &((*rover)->next);
		}
	}

	return entries_removed;
}


SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data)
{
	SListEntry *rover;

	for (rover=list; rover != NULL; rover=rover->next) {
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	/* Not found */

	return NULL;
}

int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _DevInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("??????????????????????????????");
    puts("1:) ??????????????????");
    puts("2:) ??????????????????");
    puts("3:) ??????????????????");
    puts("4:) ??????????????????");
    puts("5:) ??????????????????");
    puts("6:) ??????");
    puts("-------------------");
    puts("");
}

int insert_dev(SListEntry **list)
{
    DevInfo *dev_info;
    SListEntry *p;

    dev_info = malloc(sizeof (struct _DevInfo));
    if (dev_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

	int id;
	char deviceName[MAXBUF];
	char brandName[MAXBUF];
    char type[MAXBUF];
	double price;
	char buyTime[MAXBUF];
	char isFine[MAXBUF];

    puts("????????????id:");
    scanf("%d", &dev_info->id);
    puts("??????????????????:");
    scanf("%s", dev_info->deviceName);
    puts("??????????????????:");
    scanf("%s", dev_info->type);
    puts("??????????????????:");
    scanf("%s", dev_info->brandName);
    puts("??????????????????:");
    scanf("%s", dev_info->buyTime);
    puts("??????????????????:");
    scanf("%s", dev_info->isFine);
    puts("??????????????????:");
    scanf("%lf", &dev_info->price);
    puts("");

    if (slist_append(list, (SListValue *)dev_info) != NULL) {
        puts("----------------------");
        puts("??????????????????");
        puts("----------------------");
        return 1;
    } else {
        puts("----------------------");
        puts("??????????????????");
        puts("----------------------");
        return 0;
    }
}

int delete_dev_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _DevInfo *dev_info;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("???????????????");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        dev_info = (struct _DevInfo *) value;

        if (slist_remove_entry(entry, p) == 0) {
            puts("-------------------");
            puts("??????????????????");
            puts("-------------------");
            return -1;
        } else {
            puts("-------------------");
            puts("????????????");
            puts("-------------------");
            return 1;
        }
    }
    puts("");
}

int delete_dev(SListEntry **entry)
{
    int id;

    puts("????????????????????????id:");
    scanf("%d", &id);
    delete_dev_by_id(entry, id);

    return 1;
}

int query_dev_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("??????????????????");
        puts("-------------------");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("??????????????????\n");
        // ????????????????????????
        printf("id:%d\n", ((struct _DevInfo *)data)->id);
        printf("????????????:%s\n", ((struct _DevInfo *)data)->deviceName);
        printf("????????????:%s\n", ((struct _DevInfo *)data)->brandName);
        printf("????????????:%s\n", ((struct _DevInfo *)data)->isFine);
        printf("????????????:%s\n", ((struct _DevInfo *)data)->type);
        printf("??????:%lf\n", ((struct _DevInfo *)data)->price);
        puts("----------------------");
    }
    return 1;
}

int query_dev(SListEntry **entry)
{
    int id;

    puts("?????????????????????id:");
    scanf("%d", &id);
    query_dev_by_id(entry, id);

    return 1;
}


int modify_dev(SListEntry **entry)
{
    int id;
    SListEntry *p;

    puts("?????????id:");
    scanf("%d", &id);
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("???????????????");
        puts("-------------------");
        return -1;
    } else {

        struct _DevInfo *dev_info = (struct _DevInfo *)malloc(sizeof(struct _DevInfo));
        if (dev_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        puts("??????????????????id:");
        scanf("%d", &dev_info->id);
        puts("????????????????????????:");
        scanf("%s", dev_info->deviceName);
        puts("??????????????????:");
        scanf("%s", dev_info->brandName);
        puts("????????????????????????:");
        scanf("%lf", &dev_info->price);

        p->data = dev_info;

        puts("????????????");
    }
}

void show_device_table(SListEntry **deviceList)
{
    SListValue *value;
    SListEntry *p = *deviceList;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        printf("??????:%d\t", ((struct _DevInfo *) value)->id);
        printf("????????????:%s\n", ((struct _DevInfo *)value)->deviceName);
        printf("????????????:%s\n", ((struct _DevInfo *)value)->brandName);
        printf("????????????:%s\n", ((struct _DevInfo *)value)->isFine);
        printf("????????????:%s\n", ((struct _DevInfo *)value)->type);
        printf("??????:%lf\n", ((struct _DevInfo *)value)->price);
        printf("\n");

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("-------------------");
        puts("????????????????????????");
        puts("-------------------");
    }
}

int main(int argc, char const* argv[])
{
    int input;
    SListEntry *deviceList = NULL;
    struct _DevInfo *device;

    while (1) {
        welcome();
        puts("");
        puts("??????????????????:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                insert_dev(&deviceList);
                break;
            case 2:
                modify_dev(&deviceList);
                break;
            case 3:
                query_dev(&deviceList);
                break;
            case 4:
                show_device_table(&deviceList);
                break;
			case 5:
				delete_dev(&deviceList);
				break;
            case 6:
                exit(EXIT_SUCCESS);
            default:
                puts("-------------------");
                puts("????????????");
                puts("-------------------");
                break;
        }
    }
    return 0;
}

