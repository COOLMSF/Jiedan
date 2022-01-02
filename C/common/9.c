#include <stdio.h>

#define MAX_STR 255

struct _EmpInfo {
    char name[MAX_STR];
    char addr[MAX_STR];
    char phone_number[MAX_STR];
    char mail_number[MAX_STR];
};

typedef struct _EmpInfo EmpInfo;

int main(int argc, char *argv[])
{
    EmpInfo stu_info;

    puts("请输入学生姓名:");
    scanf("%s", stu_info.name);
    puts("请输入学生住址:");
    scanf("%s", stu_info.addr);
    puts("请输入电话号码:");
    scanf("%s", stu_info.phone_number);
    puts("请输入邮政编码:");
    scanf("%s", stu_info.mail_number);

    puts("");
    puts("结果如下:");
    printf("姓名:%s\n住址:%s\n电话:%s\n邮政编码:%s\n", stu_info.name, stu_info.addr, stu_info.phone_number, stu_info.mail_number);
}