#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

#define MAXBUF 1024


struct _Flight {
	int id;
	char startTime[MAXBUF];
    char stopTime[MAXBUF];
    double price;
};

typedef void *SListValue;
typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};

typedef struct _Flight FlightInfo;
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
    if (((struct _Flight *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用航班管理系统");
    puts("1:) 添加信息");
    puts("2:) 修改信息");
    puts("3:) 查询信息");
    puts("4:) 列出所有信息");
    puts("5:) 删除信息");
	puts("6:) 保存文件");
    puts("7:) 退出");
    puts("-------------------");
    puts("");
}

int insert_flight(SListEntry **list)
{
    FlightInfo *flight_info = NULL;


    flight_info = malloc(sizeof (struct _Flight));
	memset(flight_info, 0, sizeof(struct _Flight));
    if (flight_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }



    puts("输入id:");
    scanf("%d", &flight_info->id);
    puts("输入航班开始时间:");
    scanf("%s", flight_info->startTime);
    puts("输入航班到达时间:");
    scanf("%s", flight_info->stopTime);
    puts("输入航班价格:");
    scanf("%lf", &flight_info->price);

    if (slist_append(list, (SListValue *)flight_info) != NULL) {
        puts("----------------------");
        puts("插入成功");
        puts("----------------------");
        return 1;
    } else {
        puts("----------------------");
        puts("插入失败");
        puts("----------------------");
        return 0;
    }
}

int delete_flight_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _Flight *flight_info;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("航班不存在");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        flight_info = (struct _Flight *) value;

        if (slist_remove_entry(entry, p) == 0) {
            puts("-------------------");
            puts("删除数据失败");
            puts("-------------------");
            return -1;
        } else {
            puts("-------------------");
            puts("删除数据成功");
            puts("-------------------");
            return 1;
        }
    }
    puts("");
}

int delete_flight(SListEntry **entry)
{
    int id;

    puts("输入要删除的id:");
    scanf("%d", &id);
    delete_flight_by_id(entry, id);

    return 1;
}

int query_flight_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("未查询到数据");
        puts("-------------------");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _Flight *)data)->id);
        printf("开始时间:%s\n", ((struct _Flight *)data)->startTime);
		printf("到达时间:%s\n", ((struct _Flight *)data)->stopTime);
		printf("机票价格:%lf\n", ((struct _Flight *)data)->price);
        puts("----------------------");
    }
    return 1;
}

int query_flight(SListEntry **entry)
{
    int id;

    puts("请输入要查询航班的id:");
    scanf("%d", &id);
    query_flight_by_id(entry, id);

    return 1;
}


int modify_flight(SListEntry **entry)
{
    int id;
    SListEntry *p;

    puts("请输入id:");
    scanf("%d", &id);
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("信息不存在");
        puts("-------------------");
        return -1;
    } else {

    FlightInfo *flight_info = NULL;
    flight_info = malloc(sizeof (struct _Flight));
	memset(flight_info, 0, sizeof(struct _Flight));
    if (flight_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入新的id:");
    scanf("%d", &flight_info->id);
    puts("输入新的开始时间:");
    scanf("%s", flight_info->startTime);
    puts("输入新的到达时间:");
    scanf("%s", flight_info->stopTime);
    puts("输入新的价格:");
    scanf("%lf", &flight_info->price);
    puts("");

        p->data = flight_info;

        puts("修改成功");
    }
}

void show_flight_table(SListEntry **flightList)
{
    SListValue *value;
    SListEntry *p = *flightList;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _Flight *)value)->id);
        printf("开始时间:%s\n", ((struct _Flight *)value)->startTime);
		printf("结束时间:%s\n", ((struct _Flight *)value)->stopTime);
		printf("价格:%lf\n", ((struct _Flight *)value)->price);
		
        puts("----------------------");
        printf("\n");

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("-------------------");
        puts("未查询到任何数据");
        puts("-------------------");
    }
}

void save_file(SListEntry **flightList)
{
    SListValue *value;
    SListEntry *p = *flightList;
	FILE *fp;

	char filename[1000] = { 0 };

	puts("输入文件名：");
	scanf("%s", filename);

	fp = fopen(filename, "w");


   
    while (p != NULL) {
        value = p->data;

        fprintf(fp,"id:%d\n", ((struct _Flight *)value)->id);
        fprintf(fp,"开始时间:%s\n", ((struct _Flight *)value)->startTime);
		fprintf(fp,"到达时间:%s\n", ((struct _Flight *)value)->stopTime);
		fprintf(fp, "价格:%lf\n", ((struct _Flight *)value)->price);
        fprintf(fp,"\n");

        p = p->next;
      
    }

	puts("保存文件成功");
}


int main(int argc, char const* argv[])
{
    int input;
    SListEntry *flightList = NULL;
    

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                insert_flight(&flightList);
                break;
            case 2:
                modify_flight(&flightList);
                break;
            case 3:
                query_flight(&flightList);
                break;
            case 4:
                show_flight_table(&flightList);
                break;
			case 5:
				delete_flight(&flightList);
				break;
			case 6:
				save_file(&flightList);
				break;
            case 7:
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
