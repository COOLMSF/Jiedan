#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 255
#define MAX_SCORE_ELE 4
#define MAX_STU_ELE 3
#define MAX_SCORE_ELE 4

struct _Score {
    float Yuwen;
    float Shuxue;
    float Yingyu;
    float total;
};

struct _Student {
    int id;
    char name[MAX_STR];
    struct _Score score;
};

void print_info(struct _Student *stu_arr_ptr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("ID:%d\t����:%s\t�ܷ�:%lf\n", stu_arr_ptr[i].id, stu_arr_ptr[i].name, stu_arr_ptr[i].score.total);
        printf("����:%f\t��ѧ:%f\tӢ��:%f\n", stu_arr_ptr[i].score.Yuwen, stu_arr_ptr[i].score.Shuxue, stu_arr_ptr[i].score.Yingyu);
    }
}

void print_info_id(struct _Student *stu_arr_ptr, int size, int id)
{
    for (int i = 0; i < size; i++) {
        if (stu_arr_ptr[i].id == id) {
            printf("ID:%d\t����:%s\t�ܷ�:%lf\n", stu_arr_ptr[i].id, stu_arr_ptr[i].name, stu_arr_ptr[i].score.total);
            printf("����:%f\t��ѧ:%f\tӢ��:%f\n", stu_arr_ptr[i].score.Yuwen, stu_arr_ptr[i].score.Shuxue, stu_arr_ptr[i].score.Yingyu);
        }
    }
}

void cal_avg_score(struct _Student *stu_arr_ptr, int size)
{
    float Yuwen_total_score = 0.0;
    float Shuxue_total_score = 0.0;
    float Yingyu_total_score = 0.0;

    for (int i = 0; i < size; i++) {
        Yuwen_total_score += stu_arr_ptr[i].score.Yuwen;
        Shuxue_total_score += stu_arr_ptr[i].score.Shuxue;
        Yingyu_total_score += stu_arr_ptr[i].score.Yingyu;
    }

    printf("����ƽ����:%f\n", Yuwen_total_score / size);
    printf("��ѧƽ����:%f\n", Shuxue_total_score / size);
    printf("Ӣ��ƽ����:%f\n", Yingyu_total_score / size);
}

void modify_score_id(struct _Student *stu_arr_ptr, int size, int id)
{
    int flag = 0;
    for (int i = 0; i < size; i++) {
        if (stu_arr_ptr[i].id == id) {
            float Yuwen_score, Shuxue_score, Yingyu_score;

            puts("�������µ����ĳɼ�:");
            scanf("%f", &stu_arr_ptr[i].score.Yuwen);
            puts("�������µ���ѧ�ɼ�:");
            scanf("%f", &stu_arr_ptr[i].score.Shuxue);
            puts("�������µ�Ӣ��ɼ�:");
            scanf("%f", &stu_arr_ptr[i].score.Yingyu);
            flag++;
        }
    }

    if (flag == 0) {
        puts("id������");
    } else {
        puts("�޸ĳɹ�");
    }
}

void menu()
{
    puts("1:) ��ʾѧ����Ϣ");
    puts("2:) ��ѧ�ò���ѧ��");
    puts("3:) ������ſγ�ƽ����");
    puts("4:) ѧ���ɼ��޸�");
    puts("5:) �˳�");
}

int main()
{
    struct _Student stu_arr[MAX_STU_ELE];
    struct _Student *stu_arr_ptr = stu_arr;

    for (int i = 0; i < MAX_STU_ELE; i++) {
        printf("�������%d��ѧ������Ϣ(id, ����):", i + 1);
        scanf("%d %s", &stu_arr[i].id, stu_arr[i].name);

        double total_score = 0.0;
        printf("������ĳɼ�:");
        scanf("%f", &stu_arr[i].score.Yuwen);
        printf("�����ѧ�ɼ�:");
        scanf("%f", &stu_arr[i].score.Shuxue);
        printf("���Ӣ��ɼ�:");
        scanf("%f", &stu_arr[i].score.Yingyu);
        stu_arr[i].score.total = stu_arr[i].score.Yuwen + stu_arr[i].score.Shuxue + stu_arr[i].score.Yingyu;
    }

    while (1) {
        int c;
        int id;
        menu();

        fflush(stdin);
        printf("\n���������ѡ��:");
        scanf("%d", &c);

        switch (c) {
            case 1:
                print_info(stu_arr_ptr, MAX_STU_ELE);
                break;
            case 2:
                puts("������Ҫ��ѯ��id:");
                scanf("%d", &id);
                print_info_id(stu_arr_ptr, MAX_STU_ELE, id);
                break;
            case 3:
                cal_avg_score(stu_arr_ptr, MAX_STU_ELE);
                break;
            case 4:
                puts("������Ҫ�޸ĵ�id:");
                scanf("%d", &id);
                modify_score_id(stu_arr_ptr, MAX_STU_ELE, id);
                break;
            case 5:
                exit(EXIT_SUCCESS);
        }
    }
}

