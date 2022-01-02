#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

#define MAXBUF 1024
// 编号（不重复），姓名，性别，家庭电话，移动电话，工作单位，
// 联系地址，电子邮箱

struct _PersonInfo {
	int id;
	char name[MAXBUF];
    char gender[MAXBUF];
	char telephone[MAXBUF];
	char mobile_phone[MAXBUF];
	char company[MAXBUF];
	char address[MAXBUF];
	char mail[MAXBUF];
};

typedef void *SListValue;
typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};

#define SLIST_NULL ((void *) 0)
typedef struct _PersonInfo PersonInfo;
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
    if (((struct _PersonInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用通讯录管理系统");
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

int insert_person(SListEntry **list)
{
    PersonInfo *person_info = NULL;


    person_info = malloc(sizeof (struct _PersonInfo));
	memset(person_info, 0, sizeof(struct _PersonInfo));
    if (person_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }



    puts("输入id:");
    scanf("%d", &person_info->id);
    puts("输入名字:");
    scanf("%s", person_info->name);
    puts("输入性别:");
    scanf("%s", person_info->gender);
    puts("输入家庭电话:");
    scanf("%s", person_info->telephone);
    puts("输入移动电话:");
    scanf("%s", person_info->mobile_phone);
    puts("输入公司地址:");
    scanf("%s", person_info->company);
    puts("输入家庭地址:");
	scanf("%s", person_info->address);
	puts("输入邮件:");
	scanf("%s", person_info->mail);
    puts("");

    if (slist_append(list, (SListValue *)person_info) != NULL) {
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

int delete_person_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _PersonInfo *person_info;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("联系人不存在");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        person_info = (struct _PersonInfo *) value;

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

int delete_person(SListEntry **entry)
{
    int id;

    puts("输入要删除的联系人的id:");
    scanf("%d", &id);
    delete_person_by_id(entry, id);

    return 1;
}

int query_person_by_id(SListEntry **entry, int id)
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
        printf("id:%d\n", ((struct _PersonInfo *)data)->id);
        printf("联系人名称:%s\n", ((struct _PersonInfo *)data)->name);
		printf("联系人性别:%s\n", ((struct _PersonInfo *)data)->gender);
		printf("联系人电话:%s\n", ((struct _PersonInfo *)data)->mobile_phone);
		printf("联系人家庭电话:%s\n", ((struct _PersonInfo *)data)->telephone);
		printf("联系人性别:%s\n", ((struct _PersonInfo *)data)->gender);
		printf("联系公司地址:%s\n", ((struct _PersonInfo *)data)->company);
		printf("联系人家庭住址:%s\n", ((struct _PersonInfo *)data)->address);
		printf("联系人邮箱:%s\n", ((struct _PersonInfo *)data)->mail);
        puts("----------------------");
    }
    return 1;
}

int query_person(SListEntry **entry)
{
    int id;

    puts("请输入要查询的id:");
    scanf("%d", &id);
    query_person_by_id(entry, id);

    return 1;
}


int modify_person(SListEntry **entry)
{
    int id;
    SListEntry *p;

    puts("请输入id:");
    scanf("%d", &id);
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("联系人不存在");
        puts("-------------------");
        return -1;
    } else {

    PersonInfo *person_info = NULL;
    person_info = malloc(sizeof (struct _PersonInfo));
	memset(person_info, 0, sizeof(struct _PersonInfo));
    if (person_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入新的id:");
    scanf("%d", &person_info->id);
    puts("输入新的名字:");
    scanf("%s", person_info->name);
    puts("输入新的性别:");
    scanf("%s", person_info->gender);
    puts("输入新的家庭电话:");
    scanf("%s", person_info->telephone);
    puts("输入新的移动电话:");
    scanf("%s", person_info->mobile_phone);
    puts("输入新的公司地址:");
    scanf("%s", person_info->company);
    puts("输入新的家庭地址:");
	scanf("%s", person_info->address);
	puts("输入新的邮件:");
	scanf("%s", person_info->mail);
    puts("");

        p->data = person_info;

        puts("修改成功");
    }
}

void show_person_table(SListEntry **deviceList)
{
    SListValue *value;
    SListEntry *p = *deviceList;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _PersonInfo *)value)->id);
        printf("联系人名称:%s\n", ((struct _PersonInfo *)value)->name);
		printf("联系人性别:%s\n", ((struct _PersonInfo *)value)->gender);
		printf("联系人电话:%s\n", ((struct _PersonInfo *)value)->mobile_phone);
		printf("联系人家庭电话:%s\n", ((struct _PersonInfo *)value)->telephone);
		printf("联系人性别:%s\n", ((struct _PersonInfo *)value)->gender);
		printf("联系公司地址:%s\n", ((struct _PersonInfo *)value)->company);
		printf("联系人家庭住址:%s\n", ((struct _PersonInfo *)value)->address);
		printf("联系人邮箱:%s\n", ((struct _PersonInfo *)value)->mail);
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

void save_file(SListEntry **deviceList)
{
    SListValue *value;
    SListEntry *p = *deviceList;
	FILE *fp;

	char filename[1000] = { 0 };

	puts("输入文件名：");
	scanf("%s", filename);

	fp = fopen(filename, "w");


   
    while (p != NULL) {
        value = p->data;

        fprintf(fp,"id:%d\n", ((struct _PersonInfo *)value)->id);
        fprintf(fp,"联系人名称:%s\n", ((struct _PersonInfo *)value)->name);
		fprintf(fp,"联系人性别:%s\n", ((struct _PersonInfo *)value)->gender);
		fprintf(fp, "联系人电话:%s\n", ((struct _PersonInfo *)value)->mobile_phone);
		fprintf(fp,"联系人家庭电话:%s\n", ((struct _PersonInfo *)value)->telephone);
		fprintf(fp,"联系人性别:%s\n", ((struct _PersonInfo *)value)->gender);
		fprintf(fp,"联系公司地址:%s\n", ((struct _PersonInfo *)value)->company);
		fprintf(fp,"联系人家庭住址:%s\n", ((struct _PersonInfo *)value)->address);
		fprintf(fp,"联系人邮箱:%s\n", ((struct _PersonInfo *)value)->mail);
        fprintf(fp,"\n");

        p = p->next;
      
    }

	puts("保存文件成功");
}


int main(int argc, char const* argv[])
{
    int input;
    SListEntry *deviceList = NULL;
    struct _PersonInfo *device;

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                insert_person(&deviceList);
                break;
            case 2:
                modify_person(&deviceList);
                break;
            case 3:
                query_person(&deviceList);
                break;
            case 4:
                show_person_table(&deviceList);
                break;
			case 5:
				delete_person(&deviceList);
				break;
			case 6:
				save_file(&deviceList);
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
