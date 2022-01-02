#include <stdio.h>

#define MAX_STR 255
#define MAX_SCORE_ELE 4
#define MAX_STU_ELE 3

struct _Student {
    int id;
    char name[MAX_STR];
    double score[MAX_SCORE_ELE];
    double total_score;
};

void print_info(struct _Student *stu_arr_ptr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("ID:%d\t姓名:%s\t总分:%lf\n", stu_arr_ptr[i].id, stu_arr_ptr[i].name, stu_arr_ptr[i].total_score);
    }
}

// void cal_total_score(struct _Student *stu_arr_ptr, int size)
// {
//     for (int i = 0; i < size; i++) {
//         double total_score = 0.0;
//         for (in j = 0; j < MAX_SCORE_ELE; j++) {
//             stu_arr_ptr[i].score[j]
//         }
//     }
// }
//

void swap_stu(struct _Student *p1, struct _Student *p2)
{
    struct _Student temp;

    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort(struct _Student *stu_arr_ptr, int size)
{
    // 冒泡排序
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (stu_arr_ptr[i].total_score > stu_arr_ptr[j].total_score)
                swap_stu(&stu_arr_ptr[i], &stu_arr_ptr[j]);
        }
    }
}

int main()
{
    struct _Student stu_arr[MAX_STU_ELE];
    struct _Student *stu_arr_ptr = stu_arr;

    for (int i = 0; i < MAX_STU_ELE; i++) {
        printf("请输入第%d个学生的信息(id, 姓名，分数):", i + 1);
        scanf("%d %s", &stu_arr[i].id, stu_arr[i].name);

        printf("请输入学生成绩:");
        double total_score = 0.0;
        for (int j = 0; j < MAX_SCORE_ELE; j++) {
            scanf("%lf", &stu_arr[i].score[j]);
            total_score += stu_arr[i].score[j];
        }
        stu_arr[i].total_score = total_score;
    }
    puts("---------排序前----------");
    print_info(stu_arr_ptr, MAX_STU_ELE);
    puts("---------排序后----------");
    sort(stu_arr_ptr, MAX_STU_ELE);
    print_info(stu_arr_ptr, MAX_STU_ELE);

}

