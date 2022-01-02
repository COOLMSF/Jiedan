#include <stdlib.h>
#include <string.h>

#include "arraylist.h"
#include "carmanagement.h"

void welcome()
{
    puts("1:) 添加车辆");
    puts("2:) 删除车辆");
    puts("3:) 从硬盘读取数据");
    puts("4:) 写入数据到硬盘");
    puts("5:) 查询车辆");
    puts("6:) 显示所有车辆信息");
    puts("7:) 退出系统");
}

int append_car(ArrayList *list, ArrayListValue value)
{
    return arraylist_append(list, value);
}

int insert_car(ArrayList *list, ArrayListValue value)
{
    return arraylist_append(list, value);
}

int delete_car(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    int ret = -1;

    for (size_t i = 0; i < list->length; i++)
        if (compare_func(list->data[i], &value) == 0)
        {
            arraylist_remove(list, i);
            ret = 1;
        }
    return ret;
}

int modify_car(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    int ret = -1;

    for (size_t i = 0; i < list->length; i++)
        if (compare_func(list->data[i], &value) == 0)
        {
            arraylist_remove(list, i);
            ret = 1;
        }

    return ret;
}

Car *query_car(ArrayList *list, void *value, ArrayListCompareFunc compare_func)
{
    for (size_t i = 0; i < list->length; i++)
    {
        if (compare_func(list->data[i], &value) == 0)
            return list->data[i];
    }

    return NULL;
}

Car *new_car(void)
{
    Car *car;

    car = malloc(sizeof(struct _Car));
    if (car == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("车牌号:");
    scanf("%d", &car->id);
    puts("车主名字:");
    scanf("%s", car->owner_name);
    puts("车位(小数):");
    scanf("%lf", &car->pos);

    return car;
}

int compare_func_check_pos(void *a, void *b)
{
    Car *car1, *car2;

    car1 = (Car *)a;
    car2 = (Car *)b;

    return car1->pos - car2->pos;
}

int show_car(ArrayList *list, size_t size)
{
    if (list->length == 0) {
        puts("暂无车辆显示");
        return -1;
    }

    puts("");
    puts("所有车辆:");
    for (size_t i = 0; i < list->length; i++)
        printf("Owner:%s\tID:%d\n", ((Car *)list->data[i])->owner_name, ((Car *)list->data[i])->id);

    return 1;
}

int read_data_from_disk(FILE *fpr, ArrayList *list)
{
    char line[MAX_LINE] = {0};

    if (fpr == NULL)
        return -1;

    while (fgets(line, MAX_LINE, fpr) != NULL) {
        // malloc new memory for car
        Car *car = malloc(sizeof(struct _Car));
        if (car == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // get formatted data from buffer
        sscanf(line, "%d, %lf, %s", &car->id, &car->pos, car->owner_name);
        // append data to list
        arraylist_append(list, car);
    }
    
    puts("读入成功");

    return 1;
}

int write_data_to_disk(FILE *fpw, ArrayList *list)
{
    char line[MAX_LINE] = { 0 };
    Car *car = (Car *)list->data;

    if (fpw == NULL)
        return -1;
    
    for (int i = 0; i < list->length; i++) {
        sprintf(line, "%d, %lf, %s\n", ((Car *)list->data[i])->id, ((Car *)list->data[i])->pos, 
        ((Car *)list->data[i])->owner_name);
        fwrite(line, strlen(line), 1, fpw);
    }

    puts("写入成功");

    return 1;
}
