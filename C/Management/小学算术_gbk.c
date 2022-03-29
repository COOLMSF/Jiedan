#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAXNAME 254
#define MAXBUF 1024

#define SLIST_NULL ((void *) 0)

struct _QuestionInfo {
    int id;
    char name[MAXNAME];
    char result[MAXNAME];
};

typedef struct _QuestionInfo QuestionInfo;
typedef void *SListValue;

typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};

typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);

struct _User {
    char id[4];
    char name[MAXNAME];
    char username[MAXNAME];
    char passwd[MAXBUF];
    // ��ȷ����
    int nright;
    // ��������
    int nwrong;
    int is_admin;
    SListEntry *ordered_questions;
};

void welcome();
void pre_welcome();
void slist_free(SListEntry *list);

SListEntry *slist_append(SListEntry **list, SListValue data);
SListValue slist_data(SListEntry *listentry);

SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data);

// user inspection

// login��½�ɹ���Ӧ�÷��ص�ǰ�û�ָ�룬���򷵻�NULL
struct _User *login(SListEntry **list);
int regist(SListEntry **list);
int forget_passwd(SListEntry **list);
int is_admin();



void add_cal(SListEntry *, struct _User *);
void sub_cal(SListEntry *, struct _User *);
void mul_cal(SListEntry *, struct _User *);
void div_cal(SListEntry *, struct _User *);
void mix_cal(SListEntry *, struct _User *);
// �ֱ��5���ļ���������
int init_questions(SListEntry **add_list, SListEntry **sub_list,
    SListEntry **mul_list, SListEntry **div_list, SListEntry **mix_list);
int callback_check_id(SListValue a, SListValue b);
int callback_check_username(SListValue a, SListValue b);

int statistic(SListEntry *question_list);

int insert_user(SListEntry **list, SListValue *value);
void show_userinfo(struct _User *p);
void show_questions(SListEntry *question_list);

int is_admin(struct _User *current_user)
{
    return current_user->is_admin;
}

void pre_welcome()
{
    puts("-------------------");
    puts("��ӭʹ��Сѧ��ѧ����ϵͳ");
    puts("1:) ��½");
    puts("2:) ע��");
    puts("-------------------");
}

void add_cal(SListEntry *add_list, struct _User *user)
{
    SListEntry *p = add_list;

    puts("---�ӷ���ѵ---");

    while (p)
    {
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        printf("��Ŀ: %s\n", q->name);
        printf("��������Ĵ�:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("�ش���ȷ!\n");
            user->nright++;
        } else {
            printf("�ش����!\n");
            user->nwrong++;
        }
        p = p->next;
    }
    
}

void sub_cal(SListEntry *sub_list, struct _User *user)
{
    SListEntry *p = sub_list;

    puts("---������ѵ---");
    while (p)
    {
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        printf("��Ŀ: %s\n", q->name);
        printf("��������Ĵ�:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("�ش���ȷ!\n");
            user->nright++;
        } else {
            printf("�ش����!\n");
            user->nwrong++;
        }
        p = p->next;
    }
}

void mul_cal(SListEntry *mul_list, struct _User *user)
{
    SListEntry *p = mul_list;

    puts("---�˷���ѵ---");
    while (p)
    {
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        printf("��Ŀ: %s\n", q->name);
        printf("��������Ĵ�:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("�ش���ȷ!\n");
            user->nright++;
        } else {
            printf("�ش����!\n");
            user->nwrong++;
        }
        p = p->next;
    }

}

void div_cal(SListEntry *div_list, struct _User *user)
{
    SListEntry *p = div_list;

    puts("---������ѵ---");
    while (p)
    {
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        printf("��Ŀ: %s\n", q->name);
        printf("��������Ĵ�:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("�ش���ȷ!\n");
            user->nright++;
        } else {
            printf("�ش����!\n");
            user->nwrong++;
        }
        p = p->next;
    }

}

void mix_cal(SListEntry *mix_list, struct _User *user)
{
    SListEntry *p = mix_list;

    puts("---���������ѵ---");
    while (p)
    {
        QuestionInfo *q = p->data;
        char result[MAXBUF] = { 0 };

        printf("��Ŀ: %s\n", q->name);
        printf("��������Ĵ�:");
        scanf("%s", result);

        if (strcmp(result, q->result) == 0) {
            printf("�ش���ȷ!\n");
            user->nright++;
        } else {
            printf("�ش����!\n");
            user->nwrong++;
        }
        p = p->next;
    }

}

int main(int argc, char const* argv[])
{
    int input;
    // ����������ڴ洢���
    SListEntry *add_list = NULL, *sub_list = NULL, *mul_list = NULL, 
    *div_list = NULL, *mix_list = NULL;
    // �û��������ڴ洢�û�
    SListEntry *user_list = NULL;
    struct _User *user;
    struct _User *current_user;

start:
    while (1) {
        pre_welcome();
        puts("�������ѡ��:");
        scanf("%d", &input);

        switch (input) 
        {
            if (input > 10) {
                break;
            }
            case 1:
                if ((current_user = login(&user_list)) != NULL) {
                    puts("[+] ��½�ɹ�\n\n");
                    goto login_succeed;
                } else {
                    puts("[-] ��½ʧ��\n\n");
                    break;
                }
            case 2:
                if (regist(&user_list)) {
                    puts("[+] ע��ɹ�]\n\n");
                    break;
                } else {
                    puts("[-] ע��ʧ��\n\n");
                    break;
                }
            case 3:
                ;
        }

    }

login_succeed:
    if (!init_questions(&add_list, &sub_list, &mul_list, &div_list, &mix_list)) {
        puts("�����ļ�������");
        exit(EXIT_FAILURE);
    }

    while (1) {
        welcome();
        puts("");
        puts("�������ѡ��:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // �ӷ�����
                add_cal(add_list, current_user);
                break;
            case 2:
                // ��������
                sub_cal(sub_list, current_user);
                break;
            case 3:
                mul_cal(mul_list, current_user);
                break;
            case 4:
                div_cal(div_list, current_user);
                break;
            case 5:
                mix_cal(mix_list, current_user);
                break;
            case 6:
                break;
            case 7:
                exit(EXIT_FAILURE);
            default:
                puts("[-] �������\n\n");
                break;
        }
    }

    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("��ӭʹ��Сѧ��ѧ����ϵͳ");
    puts("1:) �ӷ�����");
    puts("2:) ��������");
    puts("3:) �˷�����");
    puts("4:) ��������");
    puts("5:) �������");
    puts("6:) ������һ��");
    puts("7:) �˳�ϵͳ");
    puts("-------------------");
    puts("");
}


struct _User *login(SListEntry **entry) 
{
    struct _User *new_user;
    SListEntry *p;
    SListValue *data;

    new_user = (struct _User *) malloc(sizeof(struct _User));

    puts("�������û���");
    scanf("%s", new_user->username);
    puts("����������:");
    scanf("%s", new_user->passwd);

    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user);
    if (p == NULL) {
        puts("[-] �û�δע��");
        return NULL;
    } else {
        data = slist_data(p);
        if (strcmp(((struct _User *)data)->username, new_user->username) == 0 &&
        strcmp(((struct _User *)data)->passwd, new_user->passwd) == 0) {
            return (struct _User *)p->data;
        }
    }
    puts("[-] �˺Ż��������");
    return NULL;
}

int regist(SListEntry **entry)
{
    struct _User *new_user;
    SListEntry *p;
    SListValue *data;
    char passwd[MAXBUF], passwd_repeat[MAXBUF];

    new_user = (struct _User *)malloc(sizeof(struct _User));
    puts("������id:");
    scanf("%s", new_user->id);
    puts("�������������:");
    scanf("%s", new_user->name);
    puts("�������û���");
    scanf("%s", new_user->username);
    puts("�Ƿ��ǹ���Ա: 0)��1)��");
    scanf("%d", &new_user->is_admin);

    while (1) 
    {
        puts("����������:");
        scanf("%s", passwd);
        puts("�����ٴ�������:");
        scanf("%s", passwd_repeat);

        if (strcmp(passwd, passwd_repeat) == 0) {
            break;
        } else {
            puts("���벻һ�£�����������:");
        }
    }

    // �������óɹ�����������
    strcpy(new_user->passwd, passwd);
    // �ҵ��û����Ƿ����
    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user->username);
    if (p == NULL) {
        if (slist_append(entry, (SListValue *)new_user)) {
            puts("[+] ע��ɹ�\n\n");
            return 1;
        }
    } else {
        puts("[-] �û���ע��\n\n");
        return -1;
    }
    puts("[-] �û�ע��ʧ��\n\n");
    return -1;
}

int init_questions(SListEntry **add_list, SListEntry **sub_list,
            SListEntry **mul_list, SListEntry **div_list, SListEntry **mix_list)
{
    // �Ӽ��˳��������������
    QuestionInfo *addition_info = NULL, *subtraction_info = NULL, 
    *multiplication_info = NULL, *division_info = NULL, *mix_operations_info = NULL;
    SListEntry *p = NULL;
    FILE *fp_add = NULL;
    FILE *fp_sub = NULL;
    FILE *fp_mul = NULL;
    FILE *fp_div = NULL;
    FILE *fp_mix = NULL;

    char add_filename[100] = "add.txt";
    char sub_filename[100] = "sub.txt";
    char mul_filename[100] = "mul.txt";
    char div_filename[100] = "div.txt";
    char mix_filename[100] = "mix.txt";
    char data[100] = { 0 };

    // printf("�����������ļ���:");
    // scanf("%s", filename);

    fp_add = fopen(add_filename, "r");
    if (!fp_add) {
        return -1;
    }
    fp_sub = fopen(sub_filename, "r");
    if (!fp_sub) {
        return -1;
    }
    fp_mul = fopen(mul_filename, "r");
    if (!fp_mul) {
        return -1;
    }
    fp_div = fopen(div_filename, "r");
    if (!fp_div) {
        return -1;
    }

    fp_mix = fopen(mix_filename, "r");
    if (!fp_mix) {
        return -1;
    }

    while (fgets(data, 100, fp_add)) {
        addition_info = malloc(sizeof (struct _QuestionInfo));
        if (addition_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%s %s",addition_info->name, addition_info->result);

        if (slist_append(add_list, (SListValue *)addition_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
        } else {
            puts("[-] ����ʧ��\n\n");
        }

        // p = slist_find_data(*add_list, callback_check_id, (SListValue *)&addition_info->id);
        // if (p == NULL) {
        //     if (slist_append(add_list, (SListValue *)addition_info) != NULL) {
        //         puts("[+] ����ɹ�\n\n");
        //     } else {
        //         puts("[-] ����ʧ��\n\n");
        //     }
        // } else {
        //     puts("[-] �Ѵ���\n\n");
        // }
    }
    puts("��ȡ�ӷ����ݳɹ�");

    while (fgets(data, 100, fp_sub)) {
        subtraction_info = malloc(sizeof (struct _QuestionInfo));
        // memset(subtraction_info, 0, sizeof(subtraction_info));
        if (subtraction_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%s %s\n",subtraction_info->name, subtraction_info->result);

        if (slist_append(sub_list, (SListValue *)subtraction_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
        } else {
            puts("[-] ����ʧ��\n\n");
        }
    }
    puts("��ȡ�����ɹ�");


    while (fgets(data, 100, fp_mul)) {
        multiplication_info = malloc(sizeof (struct _QuestionInfo));
        if (multiplication_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%s %s",multiplication_info->name, multiplication_info->result);

        if (slist_append(mul_list, (SListValue *)multiplication_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
        } else {
            puts("[-] ����ʧ��\n\n");
        }

    }
    puts("�˷����سɹ�");

    while (fgets(data, 100, fp_div)) {
        division_info = malloc(sizeof (struct _QuestionInfo));
        if (division_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%s %s", division_info->name, division_info->result);

        if (slist_append(div_list, (SListValue *)division_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
        } else {
            puts("[-] ����ʧ��\n\n");
        }

    }

    while (fgets(data, 100, fp_mix)) {
        mix_operations_info = malloc(sizeof (struct _QuestionInfo));
        if (mix_operations_info == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        sscanf(data, "%s %s", mix_operations_info->name, mix_operations_info->result);

        if (slist_append(mix_list, (SListValue *)mix_operations_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
        } else {
            puts("[-] ����ʧ��\n\n");
        }

    }
    puts("�������سɹ�");

    fclose(fp_add);
    fclose(fp_sub);
    fclose(fp_mul);
    fclose(fp_div);

    return 1;
}


int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _QuestionInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

int callback_check_username(SListValue a, SListValue b)
{
    if (strcmp(((struct _User *)a)->username, ((struct _User *)b)->username) == 0)
        return 1;
    else
        return 0;
}


int insert_user(SListEntry **list, SListValue *user)
{
    SListEntry *p;

    if (slist_append(list, (SListValue *)user) != NULL) {
        puts("[+] �����û��ɹ�\n\n");
        return 1;
    } else { puts("[-] �����û�ʧ��\n\n");
        return 0;
    }
}

void slist_free(SListEntry *list)
{
	SListEntry *entry;

	/* Iterate over each entry, freeing each list entry, until the
	 * end is reached */

	entry = list;

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

		/* Find the end of list */

		for (rover=*list; rover->next != NULL; rover = rover->next);

		/* Add to the end of list */

		rover->next = newentry;
	}

	return newentry;
}

SListValue slist_data(SListEntry *listentry)
{
	return listentry->data;
}




SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data)
{
	SListEntry *rover;

	/* Iterate over entries in the list until the data is found */

	for (rover=list; rover != NULL; rover=rover->next) {
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	/* Not found */

	return NULL;
}

