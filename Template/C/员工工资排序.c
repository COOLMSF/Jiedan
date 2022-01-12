#include <stdio.h>

#define MAX_STR 255

struct _Employee {
    int id;
    char name[MAX_STR];
    double base_salary;
    double post_salary;
};


void print_info(struct _Employee emp)
{
    printf("ID:%d\t姓名:%s\t基本工资:%lf\t职务工资:%lf\n", emp.id, emp.name, emp.base_salary, emp.post_salary);
}

void find_min_salary(struct _Employee *emp_pointer, int size)
{
    int min_index = 0;
    double cur_total_salary = 0.0;
    double next_total_salary = 0.0;

    // find min index
    for (int i = 0; i < size - 1 -1; i++) {
        cur_total_salary = emp_pointer[i].base_salary + emp_pointer[i].post_salary;
        next_total_salary = emp_pointer[i + 1].base_salary + emp_pointer[i + 1].post_salary;
        printf("cur_total_salary:%lf\n", cur_total_salary);
        printf("next_total_salary:%lf\n", next_total_salary);

        if (next_total_salary < cur_total_salary) {
            min_index = i + 1;
        } else {
            min_index = i;
        }
    }

    print_info(emp_pointer[min_index]);
}

int main()
{
    struct _Employee emp_arr[10];
    struct _Employee *p = &emp_arr[0];

    for (int i = 0; i < 10; i++) {
        printf("请输入第%d个员工的id,姓名,基本工资,职务工资:\n", i+1);
        scanf("%d %s %lf %lf", &emp_arr[i].id, emp_arr[i].name, &emp_arr[i].base_salary, &emp_arr[i].post_salary);
    }

    find_min_salary(p, 10);
}
