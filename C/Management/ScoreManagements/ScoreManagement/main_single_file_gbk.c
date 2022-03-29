#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAXNAME 254
#define MAXBUF 1024
#define NCOURSE 5


// 学生信息结构体
struct _StuInfo {
    // id
    int id;

    // 姓名
    char name[MAXNAME];

    // 专业
    char major[MAXNAME];

    // 分数
    double score[NCOURSE];


    int term; // 学期

    // 总分
    double total_score;

    // 平均分数
    double avg_score;
};

typedef void *SListValue;

// 链表结构体
typedef struct _SListEntry SListEntry;
struct _SListEntry {
    // 值域
	SListValue data;

    // 指针域
	SListEntry *next;
};

#define SLIST_NULL ((void *) 0)

// 比较调函数
typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);

// 相等回调函数
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);

void slist_free(SListEntry *list);

// 添加节点
SListEntry *slist_append(SListEntry **list, SListValue data);

// 返回下一个节点
SListEntry *slist_next(SListEntry *listentry);

// 返回节点数据
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


// 定义类型
typedef struct _StuInfo StuInfo;
typedef void *SListValue;

#define SLIST_NULL ((void *) 0)

typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);
int callback_check_id(SListValue a, SListValue b);

// 释放节点
void slist_free(SListEntry *list);

// 欢迎菜单1
void welcome();

void print_modify_info();

// 添加数据
int insert_info(SListEntry **list);

// 删除数据
int delete_info(SListEntry **list);

// 根据id删除
int delete_info_by_id(SListEntry **list, int id);

// 修改数据
int modify_info(SListEntry **list);

// 查找数据
int query_info(SListEntry **list);

// 根据id查找数据
int query_info_by_id(SListEntry **list, int id);

// 检查id的回调函数
int callback_check_id(SListValue a, SListValue b);

// 交换节点
int swap_entry(SListEntry *entry1, SListEntry *entry2);

// 分数排序
int sorted_by_total_score(SListEntry **info_list);

// 打印分数
int print_score(SListEntry **info_list);

// 打印排序后的分数
int print_orderd_total_score(SListEntry **info_list);

// 交换小数
int swap_double(double *p1, double *p2);


void slist_free(SListEntry *list)
{
	SListEntry *entry;


	entry = list;

    // 扫描所有节点
	while (entry != NULL) {
		SListEntry *next;

		next = entry->next;

        // 释放每一个节点
		free(entry);

        // 指向下一个节点
		entry = next;
	}
}


SListEntry *slist_next(SListEntry *listentry)
{
    // 返回下一个节点
	return listentry->next;
}

SListEntry *slist_append(SListEntry **list, SListValue data)
{
	SListEntry *rover;
	SListEntry *newentry;

    // 为节点分配内存
	newentry = malloc(sizeof(SListEntry));

    // 如果分配出错
	if (newentry == NULL) {
		return NULL;
	}

    // 赋值
	newentry->data = data;
	newentry->next = NULL;

    // 如果链表没有数据
	if (*list == NULL) {

		*list = newentry;

	} else {

        // 如果链表有数据，
        // 遍历所有节点，直到节点最后的位置
		for (rover=*list; rover->next != NULL; rover = rover->next);

        // 在最后一个节点插入数据
		rover->next = newentry;
	}
    // 返回节点
	return newentry;
}

SListValue slist_data(SListEntry *listentry)
{
    // 返回数据
	return listentry->data;
}

int slist_remove_entry(SListEntry **list, SListEntry *entry)
{
	SListEntry *rover;

    // 如果链表没有数据
	if (*list == NULL || entry == NULL) {
		return 0;
	}

    // 删除的节点只有一个
	if (*list == entry) {

		*list = entry->next;

	} else {

		rover = *list;

        // 找到指定节点
		while (rover != NULL && rover->next != entry) {
			rover = rover->next;
		}

		if (rover == NULL) {

            // 没有找到该节点
			return 0;

		} else {

			rover->next = entry->next;
		}
	}

    // 释放节点
	free(entry);

	return 1;
}


SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data)
{
	SListEntry *rover;

    // 扫描所有节点
	for (rover=list; rover != NULL; rover=rover->next) {
        // 使用回调函数找到对应数据
		if (callback(rover->data, data) != 0) {
            // 返回找到的数据
			return rover;
		}
	}

    // 没有找到数据
	return NULL;
}



void welcome()
{
    puts("");
    puts("-------------------");
    puts("欢迎使用成绩管理系统");
    puts("1:) 添加学生信息");
    puts("2:) 删除学生信息");
    puts("3:) 修改学生信息");
    puts("4:) 查询学生信息");
    puts("5:) 学生成绩排序");
    puts("6:) 退出");
    puts("-------------------");
    puts("");
}

int insert_info(SListEntry **list)
{
    StuInfo *stu_info;
    SListEntry *p;

    // 分配内存
    stu_info = malloc(sizeof (struct _StuInfo));
    if (stu_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("输入你的id:");
    scanf("%d", &stu_info->id);
    puts("输入你的名字:");
    scanf("%s", stu_info->name);
    puts("输入你的专业:");
    scanf("%s", stu_info->major);
    puts("请输入学期:");
    scanf("%d", &stu_info->term);
    puts("输入课程成绩:");

    // 输入分数
    for (int i = 0; i < NCOURSE; i++) {
        scanf("%lf", stu_info->score+i);
    }
    puts("");

    double avg_score = 0.0;
    double total_score = 0.0;

    // 计算总分
    for (int i = 0; i < NCOURSE; i++)
        total_score += stu_info->score[i];

    // 计算平均分
    avg_score = total_score / NCOURSE;

    // 插入总分，平均分
    stu_info->total_score = total_score;
    stu_info->avg_score = avg_score;

    // 找到对应节点
    p = slist_find_data(*list, callback_check_id, (SListValue *)&stu_info->id);
    if (p == NULL) {
        // 插入
        if (slist_append(list, (SListValue *)stu_info) != NULL) {
            puts("-------------------");
            puts("插入成功");
            puts("-------------------");
            return 1;
        } else {
            puts("-------------------");
            puts("插入失败");
            puts("-------------------");
            return 0;
        }
    } else {
        puts("信息已经存在");
        return -1;
    }
}

int delete_info(SListEntry **entry)
{
    int id;

    puts("输入要删除信息的id:");
    scanf("%d", &id);
    delete_info_by_id(entry, id);

    return 1;
}

int delete_info_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _StuInfo *stu_info;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("信息不存在");
        puts("-------------------");
        return -1;
    } else {
        if (slist_remove_entry(entry, p) == 0) {
            puts("-------------------");
            puts("删除数据失败");
            puts("-------------------");
            return -1;
        } else {
            puts("-------------------");
            puts("删除成功");
            puts("-------------------");
            return 1;
        }
    }
    puts("");
}

int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _StuInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

int query_info_by_id(SListEntry **entry, int id)
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
        printf("id:%d\n", ((struct _StuInfo *)data)->id);
        printf("姓名:%s\n", ((struct _StuInfo *)data)->name);
        printf("专业:%s\n", ((struct _StuInfo *)data)->major);
        printf("成绩总分:%lf\n", ((struct _StuInfo *)data)->total_score);
        printf("成绩平均分:%lf\n", ((struct _StuInfo *)data)->avg_score);
        puts("----------------------");
    }
    return 1;
}
int query_info(SListEntry **entry)
{
    int id;

    puts("请输入要查询的id:");
    scanf("%d", &id);
    query_info_by_id(entry, id);

    return 1;
}


int modify_info(SListEntry **entry)
{
    int id;
    SListEntry *p;

    puts("输入你要修改的id:");
    scanf("%d", &id);

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("信息不存在");
        puts("-------------------");
        return -1;
    } else {
        int c;

        while (1) {
            print_modify_info();
            puts("");
            puts("输入你的选择:");
            scanf("%d", &c);

            switch (c) {
                case 1:
                    puts("输入修改后的id:");
                    scanf("%d", &((struct _StuInfo *)p->data)->id);
                    puts("修改成功");
                    break;
                case 2:
                    puts("输入修改后的姓名:");
                    scanf("%s", ((struct _StuInfo *)p->data)->name);
                    puts("修改成功");
                    break;
                case 3:
                    puts("输入修改后的专业:");
                    scanf("%s", ((struct _StuInfo *)p->data)->major);
                    puts("修改成功");
                    break;
                case 4:
                    puts("输入修改后的分数:");

                    for (int i = 0; i < NCOURSE; i++)
                        scanf("%lf", &((struct _StuInfo *)p->data)->score[i]);
                    puts("修改成功");

                    // 修改完成后需要重新计算总分和平均分
                    double total_score = 0.0;
                    double avg_score = 0.0;

                    for (int i = 0; i < NCOURSE; i++)
                        total_score += ((struct _StuInfo *)p->data)->score[i];
                    avg_score = total_score / NCOURSE;

                    // 重新赋值
                    ((struct _StuInfo *)p->data)->total_score = total_score;
                    ((struct _StuInfo *)p->data)->avg_score = avg_score;
                    break;
                case 5:
                    goto end;
                default:
                    puts("输入有误");
            }
        }
    }

end:
    puts("");
    puts("");

}

void print_modify_info()
{
    puts("1:) 修改id");
    puts("2:) 修改姓名");
    puts("3:) 修改专业");
    puts("4:) 修改分数");
    puts("5:) 退出修改");
}

int print_orderd_total_score(SListEntry **info_list)
{
    int c;
    SListEntry *p;

    // 记录元素数量
    for (p = *info_list; p != NULL; p = slist_next(p))
        c++;

    // 定义数组，用于存储分数
    double arr[c];

    int k = 0;
    // 从链表获取数据，存储到数组
    for (p = *info_list; p != NULL; p = slist_next(p))
        arr[k++] = ((struct _StuInfo *)p->data)->total_score;

    // 冒泡排序
    for (int i = 0; i < c; i++) {
        for (int j = i; j < c; j++) {
            if (arr[i] > arr[j])
                swap_double(arr+i, arr+j);
        }
    }

    // 输出结果
    for (int i = 0; i < c; i++)
        printf("%lf ", arr[i]);
}

int swap_double(double *p1, double *p2)
{
    double tmp;

    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

int main(int argc, char const* argv[])
{
    int input;
    // 信息链表
    SListEntry *info_list = NULL;

    while (1) {
        welcome();
        puts("");
        puts("输入你的选择:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // 插入
                insert_info(&info_list);
                break;
            case 2:
                // 删除
                delete_info(&info_list);
                break;
            case 3:
                // 修改
                modify_info(&info_list);
                break;
            case 4:
                // 查询
                query_info(&info_list);
                break;
            case 5:
                print_orderd_total_score(&info_list);
                break;
            case 6:
                exit(EXIT_FAILURE);
            default:
                puts("-------------------");
                puts("输入错误");
                puts("-------------------");
                break;
        }
    }

    slist_free(info_list);
    return 0;
}
