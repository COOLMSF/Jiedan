#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAXNAME 254
#define MAXBUF 1024
#define MAXgood 100

// 结构体重命名为类型
typedef struct _TeamInfo teamInfo;
typedef struct _PeopleInfo peopleInfo;
typedef void *SListValue;

// 链表结构体
typedef struct _SListEntry SListEntry;
struct _SListEntry {
    // 链表的值域
	SListValue data;
    // 链表的指针域
	SListEntry *next;
};

// 球员的结构体信息
struct _PeopleInfo {
    // id
    int id;
    // 年龄
    int age;
    char name[MAXNAME];
    char team_name[MAXNAME];
    char phone[MAXNAME];
    // 位置
    char pos[MAXNAME];
    // 性别
    char gender[MAXNAME];
    char comp[MAXNAME];
};

struct _TeamInfo {
    int id;
    char name[MAXNAME];
    char resp_people[MAXNAME];
    // 位置
    char pos[MAXNAME];
    SListEntry *people;
};



#define SLIST_NULL ((void *) 0)

// 函数指针，用户比较变量
typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);

// 显示菜单
void welcome();
// 释放节点
void slist_free(SListEntry *list);

// 添加节点
SListEntry *slist_append(SListEntry **list, SListValue data);

// 指向下一个节点
SListEntry *slist_next(SListEntry *listentry);

// 获取值域
SListValue slist_data(SListEntry *listentry);


// 删除节点
int slist_remove_entry(SListEntry **list, SListEntry *entry);

// 删除数据
unsigned int slist_remove_data(SListEntry **list,
                               SListEqualFunc callback,
                               SListValue data);

// 查找数据
SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data);



// user inspection

// login登陆成功，应该返回当前用户指针，否则返回NULL
struct _Enroll *login(SListEntry **list);

// 插入球员
int insert_people(SListEntry **list);
// 删除球员
int delete_team(SListEntry **list);
// 按照id删除球员
int delete_people_by_id(SListEntry **list, int id);
// 修改球员
int modify_people(SListEntry **list);
// 查找球员
int query_people(SListEntry **list);
// 查询id
int query_people_by_id(SListEntry **list, int id);

// 插入球队
int insert_team(SListEntry **list);
// 删除球队
int delete_team(SListEntry **list);
// 按照id删除球队
int delete_team_by_id(SListEntry **list, int id);
// 修改球队
int modify_team(SListEntry **list);
// 查询球队
int query_team(SListEntry **list);
// 按照id查询球队
int query_team_by_id(SListEntry **list, int id);

int insert_enroll(SListEntry **people_list);
int delete_enroll(SListEntry **people_list);
int delete_enroll_by_id(SListEntry **list, int id);
int modify_enroll(SListEntry **team_list);
int query_enroll(SListEntry **list);
int query_enroll_by_id(SListEntry **list, int id);

int callback_check_id(SListValue a, SListValue b);
int insert_user(SListEntry **list, SListValue *value);
void show_userinfo(struct _Enroll *p);
void show_people(SListEntry *people_list);


void pre_welcome()
{
    puts("1:) 登陆");
    puts("2:) 注册");
    puts("3:) 忘记密码");
}

int main(int argc, char const* argv[])
{
    int input;
    // 球员链表，用于存储球员
    SListEntry *people_list = NULL;
    // 球队链表，用于存储球队
    SListEntry *team_list = NULL;
    // 报名链表，用于报名信息
    SListEntry *enroll_list = NULL;

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // 添加球员
                insert_people(&people_list);
                break;
            case 2:
                // 删除球员
                delete_team(&people_list);
                break;
            case 3:
                // 修改球员
                modify_people(&people_list);
                break;
            case 4:
                query_people(&people_list);
                break;


            case 5:
                insert_team(&team_list);
                break;
            case 6:
                delete_team(&team_list);
                break;
            case 7:
                modify_team(&team_list);
                break;
            case 8:
                query_team(&team_list);
                break;
            
            case 9:
                insert_enroll(&enroll_list);
                break;
            case 10:
                delete_enroll(&enroll_list);
                break;
            case 11:
                modify_team(&enroll_list);
                break;
            case 12:
                query_team(&enroll_list);
                break;

            case 13:
                exit(-1);
            
            default:
                puts("[-] 输入错误\n\n");
                break;
        }
    }

    slist_free(people_list);
    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用球员管理系统");
    puts("1:) 添加球员");
    puts("2:) 删除球员");
    puts("3:) 修改球员");
    puts("4:) 查询球员");

    puts("5:) 添加球队");
    puts("6:) 删除球队");
    puts("7:) 修改球队");
    puts("8:) 查询球队");

    puts("9:) 增加报名信息");
    puts("10:) 删除报名信息");
    puts("11:) 修改报名信息");
    puts("12:) 查询报名信息");
    puts("13:) 退出");
    puts("-------------------");
    puts("");
}


// 检查id的回调函数
int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _TeamInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}



// 插入球员
int insert_people(SListEntry **list)
{
    // 球员信息
    peopleInfo *people_info;
    SListEntry *p;

    // 分配内存
    people_info = malloc(sizeof (struct _TeamInfo));
    if (people_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入球员id:");
    scanf("%d", &people_info->id);
    puts("输入球员名字:");
    scanf("%s", people_info->name);
    puts("输入球员年龄:");
    scanf("%d", &people_info->age);
    puts("输入球员球队性别:");
    scanf("%s", people_info->gender);
    puts("输入球员电话:");
    scanf("%s", people_info->phone);
    puts("输入球员位置:");
    scanf("%s", people_info->pos);
    puts("输入球员球队名称:");
    scanf("%s", people_info->team_name);
    puts("");

    // 查找信息
    p = slist_find_data(*list, callback_check_id, (SListValue *)&people_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)people_info) != NULL) {
            puts("[+] 插入成功\n\n");
            return 1;
        } else {
            puts("[-] 插入失败\n\n");
            return 0;
        }
    } else {
        puts("[-] 此球员已存在\n\n");
        return -1;
    }
    return 1;
}

int delete_people(SListEntry **entry)
{
    int id;

    puts("输入要删除球员的id:");
    scanf("%d", &id);
    delete_people_by_id(entry, id);

    return 1;
}

int delete_people_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _TeamInfo *people_info;

    // 找到节点，并且删除
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("此球员不存在");
        puts("-------------------");
        return -1;
    } else {
        // 返回数据
        value = slist_data(p);
        // 分配内存
        people_info = (struct _TeamInfo *) value;
        if (slist_remove_entry(entry, p) == 0) {
            puts("[-] 删除数据失败\n\n");
            return -1;
        } else {
            puts("[+] 删除成功\n\n");
            return 1;
        }
    }
    puts("");
}




// 查询球员
int query_people(SListEntry **entry)
{
    int id;

    puts("请输入要查询的id:");
    scanf("%d", &id);
    query_people_by_id(entry, id);

    return 1;
}

// 根据id查询球员
int query_people_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    // 使用回掉函数，查找相应id的用户
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("[-] 未查询到数据\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _PeopleInfo *)data)->id);
        printf("名字:%s\n", ((struct _PeopleInfo *)data)->name);
        printf("性别:%d\n", ((struct _PeopleInfo *)data)->age);
        printf("电话:%s\n", ((struct _PeopleInfo *)data)->phone);
        printf("位置:%s\n", ((struct _PeopleInfo *)data)->pos);
        printf("球队名称:%s\n", ((struct _PeopleInfo *)data)->team_name);
        puts("----------------------");
    }
    return 1;
}

int modify_people(SListEntry **entry)
{
    return 0;
}


//------------------------- 球队

// 插入球队
int insert_team(SListEntry **list)
{
    // 球员信息
    teamInfo *team_info;
    SListEntry *p;

    // 分配内存
    team_info = malloc(sizeof (struct _TeamInfo));
    if (team_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入球id:");
    scanf("%d", &team_info->id);
    puts("输入球队:");
    scanf("%s", team_info->name);
    puts("输入球队地点:");
    scanf("%s", team_info->pos);
    puts("输入球队负责人:");
    scanf("%s", team_info->resp_people);
    puts("");

    p = slist_find_data(*list, callback_check_id, (SListValue *)&team_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)team_info) != NULL) {
            puts("[+] 插入成功\n\n");
            return 1;
        } else {
            puts("[-] 插入失败\n\n");
            return 0;
        }
    } else {
        puts("[-] 此球队\n\n");
        return -1;
    }
    return 1;
}

int delete_team(SListEntry **entry)
{
    int id;

    puts("输入要删除球队id:");
    scanf("%d", &id);
    delete_team_by_id(entry, id);

    return 1;
}

int delete_team_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _TeamInfo *people_info;

    // 找到节点，并且删除
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("此球队不存在");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        people_info = (struct _TeamInfo *) value;
        if (slist_remove_entry(entry, p) == 0) {
            puts("[-] 删除数据失败\n\n");
            return -1;
        } else {
            puts("[+] 删除成功\n\n");
            return 1;
        }
    }
    puts("");
}


// 查询球队
int query_team(SListEntry **entry)
{
    int id;

    puts("请输入要查询的id:");
    scanf("%d", &id);
    query_team_by_id(entry, id);

    return 1;
}

// 根据id查询球队
int query_team_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("[-] 未查询到数据\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _PeopleInfo *)data)->id);
        printf("名字:%s\n", ((struct _PeopleInfo *)data)->name);
        printf("性别:%d\n", ((struct _PeopleInfo *)data)->age);
        printf("电话:%s\n", ((struct _PeopleInfo *)data)->phone);
        printf("位置:%s\n", ((struct _PeopleInfo *)data)->pos);
        printf("球队名称:%s\n", ((struct _PeopleInfo *)data)->team_name);
        puts("----------------------");
    }
    return 1;
}

int modify_team(SListEntry **entry)
{
    return 0;
}


// ------------- 报名



int insert_enroll(SListEntry **list)
{
    // 球员信息
    peopleInfo *people_info;
    SListEntry *p, *q;

    int people_id;
    int team_id;

    // 分配内存
    people_info = malloc(sizeof (struct _TeamInfo));
    if (people_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入球员id:");
    scanf("%d", &people_info->id);
    puts("");

    puts("输入球员姓名:");
    scanf("%s", people_info->name);
    puts("");

    puts("输入要加入的球队名称:");
    scanf("%s", people_info->team_name);
    puts("");

    puts("输入要加入的比赛名称:");
    scanf("%s", people_info->comp);
    puts("");


        if (slist_append(list, (SListValue *)people_info) != NULL) {
            puts("[+] 插入成功\n\n");
            return 1;
        } else {
            puts("[-] 插入失败\n\n");
            return 0;
        }
    return 1;
}

int delete_enroll(SListEntry **entry)
{
    int id;

    puts("输入要删除报名的id:");
    scanf("%d", &id);
    delete_people_by_id(entry, id);

    return 1;
}

int delete_enroll_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _TeamInfo *people_info;

    // 找到节点，并且删除
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("未报名");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        people_info = (struct _TeamInfo *) value;
        if (slist_remove_entry(entry, p) == 0) {
            puts("[-] 删除数据失败\n\n");
            return -1;
        } else {
            puts("[+] 删除成功\n\n");
            return 1;
        }
    }
    puts("");
}




// 查询报名
int query_enroll(SListEntry **entry)
{
    int id;

    puts("请输入要查询的id:");
    scanf("%d", &id);
    query_people_by_id(entry, id);

    return 1;
}

// 根据id查询报名
int query_enroll_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    // 查找数据
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("[-] 未查询到数据\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("查询结果如下\n");
        // 这里需要强制转换
        printf("id:%d\n", ((struct _PeopleInfo *)data)->id);
        printf("名字:%s\n", ((struct _PeopleInfo *)data)->name);
        printf("性别:%d\n", ((struct _PeopleInfo *)data)->age);
        printf("电话:%s\n", ((struct _PeopleInfo *)data)->phone);
        printf("位置:%s\n", ((struct _PeopleInfo *)data)->pos);
        printf("球队名称:%s\n", ((struct _PeopleInfo *)data)->team_name);
        printf("比赛名称:%s\n", ((struct _PeopleInfo *)data)->comp);
        puts("----------------------");
    }
    return 1;
}



void slist_free(SListEntry *list)
{
	SListEntry *entry;

	entry = list;

    // 扫描链表
	while (entry != NULL) {
		SListEntry *next;

		next = entry->next;

		free(entry);

		entry = next;
	}
}


SListEntry *slist_append(SListEntry **list, SListValue data)
{
	SListEntry *rover;
	SListEntry *newentry;

    // 分配内存
	newentry = malloc(sizeof(SListEntry));

	if (newentry == NULL) {
		return NULL;
	}

	newentry->data = data;
	newentry->next = NULL;


	if (*list == NULL) {


		*list = newentry;

	} else {

        // 扫描到链表末尾
		for (rover=*list; rover->next != NULL; rover = rover->next);
        // 添加节点到末尾
		rover->next = newentry;
	}

	return newentry;
}

SListValue slist_data(SListEntry *listentry)
{
	return listentry->data;
}


SListEntry *slist_next(SListEntry *listentry)
{
	return listentry->next;
}

int slist_remove_entry(SListEntry **list, SListEntry *entry)
{
	SListEntry *rover;


    // 节点为空
	if (*list == NULL || entry == NULL) {
		return 0;
	}

	if (*list == entry) {


		*list = entry->next;

	} else {


		rover = *list;

        // 扫面链表
		while (rover != NULL && rover->next != entry) {
			rover = rover->next;
		}

		if (rover == NULL) {


			return 0;

		} else {
            // 指向下一个节点
			rover->next = entry->next;
		}
	}


	free(entry);


	return 1;
}



SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data)
{
	SListEntry *rover;


    // 遍历链表
	for (rover=list; rover != NULL; rover=rover->next) {
        // 调用回调函数检查
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	return NULL;
}

