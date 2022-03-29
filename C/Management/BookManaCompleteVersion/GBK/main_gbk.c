#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "slist.h"

#define MAXNAME 254
#define MAXBUF 1024
#define MAXBOOK 100

struct _BookInfo {
    char id[4];
    char name[MAXNAME];
    char author_name[MAXNAME];
    enum { Novel, Classic, Tech } type;
    double price;
    int total_num;
    int left_num;
    // int borrow_time;
    // int return_time;
    // int max_borrow_time;
    // time_t borrowed_time;
};
typedef struct _BookInfo BookInfo;

struct _User {
    char id[4];
    int num_borrow;
    int max_num_borrow;
    char gender[MAXNAME];
    char name[MAXNAME];
    char username[MAXNAME];
    char passwd[MAXBUF];
    SListEntry *borrowed_book;
    enum { TEACHER, STUDENT } type;
};

void welcome();
void pre_welcome();

// user inspection

// login��½�ɹ���Ӧ�÷��ص�ǰ�û�ָ�룬���򷵻�NULL
struct _User *login(SListEntry **list);
int regist(SListEntry **list);
int forget_passwd(SListEntry **list);

int insert_book(SListEntry **list);
int delete_book(SListEntry **list);
int delete_book_by_id(SListEntry **list, int id);
int modify_book(SListEntry **list);
int query_book(SListEntry **list);
int query_book_by_id(SListEntry **list, char *id);
int callback_check_str_id(SListValue a, SListValue b);
int callback_check_id(SListValue a, SListValue b);
int callback_check_username(SListValue a, SListValue b);

int borrow_book(struct _User *user, SListEntry **book_list);
int return_book(struct _User *user,SListEntry **book_list);
int statistic(SListEntry *book_list);

// ��ʼ��ѧ���ͽ�ʦ���Խ���������������
void teacher_borrow(struct _BookInfo *p);
void student_borrow(struct _BookInfo *p);
struct _User *ask_user_info(struct _User *p);
int insert_user(SListEntry **list, SListValue *value);
void show_userinfo(struct _User *p);
void show_books(SListEntry *book_list);

// ��Ϣ�洢
// ���û���Ϣ�洢���ļ�
int user_save_list_to_file(const char *filename, SListEntry *list);
// ���ļ���ȡ�û���Ϣ
int user_read_file_to_list(const char *filename, SListEntry **list);

// ͬ��
int book_save_list_to_file(const char *filename, SListEntry *list);
int book_read_file_to_list(const char *filename, SListEntry **list);

int book_save_list_to_file(const char *filename, SListEntry *list)
{
    FILE *fp = NULL;
    char buff[MAXBUF] = { 0 };
    SListEntry *p = list;

    fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // ������һ�����⣬��Ȼÿ�ζ�Ҫ����������
    // ��ȡ���ݵ�����ʹ�ã�ֻ�Ǹ���fp
    // ���ַ��������⣬ֻ���ֶ���ӡ����
    // fgets(buff, MAXBUF, fp);
    fprintf(fp, "ͼ���� ͼ������ ͼ��۸� ͼ������ �ִ�����\n");

    while (p) {
        struct _BookInfo *book_ptr = p->data;

        // д�����ݵ��ļ�
        fprintf(fp, "%s %s %lf %d %d\n", book_ptr->id, book_ptr->name,
        book_ptr->price, book_ptr->total_num, book_ptr->left_num);

        // ָ����һ���ڵ�
        p = p->next;
    }

    fclose(fp);
}

int book_read_file_to_list(const char *filename, SListEntry **list)
{
    FILE *fp = NULL;
    char buff[MAXBUF] = { 0 };

    fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // ������һ�У���һ���Ǳ���
    fgets(buff, MAXBUF, fp);

    SListEntry *p;
    // ��ʼ��ȡ��������
    while (fgets(buff, MAXBUF, fp) > 0) {
        // �������ڴ�
        struct _BookInfo *book_ptr = malloc(sizeof (struct _BookInfo));
        if (!book_ptr) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        memset(book_ptr, 0, sizeof(struct _BookInfo));

        // �ӻ�������ȡ���ݵ��ṹ��
        sscanf(buff, "%s %s %lf %d %d", book_ptr->id,
        book_ptr->name, &book_ptr->price, 
        &book_ptr->total_num, &book_ptr->left_num);

        if (book_ptr == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // ��������
        p = slist_find_data(*list, callback_check_str_id, (SListValue *)&book_ptr->id);
        // ����pΪ�յ�ʱ��Ҳ����˵���鼮������
        if (p == NULL) {
            if (slist_append(list, (SListValue *)book_ptr) != NULL) {
                puts("[+] ����ɹ�\n\n");
            } else {
                puts("[-] ����ʧ��\n\n");
            }
        } else {
            puts("[-] �鼮�Ѵ���\n\n");
            return -1;
        }

    }

    fclose(fp);
}

int user_save_list_to_file(const char *filename, SListEntry *list)
{
    FILE *fp = NULL;
    char buff[MAXBUF] = { 0 };
    SListEntry *p = list;

    fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "ͼ��֤�� ���� �Ա� �������� ���������� ����\n");
    while (p) {
        struct _User *user_ptr = ((struct _User *)p->data);

        // д�����ݵ��ļ�
        fprintf(fp, "%s %s %s %d %d %s\n", user_ptr->id, user_ptr->username,
        user_ptr->gender, user_ptr->num_borrow, user_ptr->max_num_borrow, user_ptr->passwd);

        // ָ����һ���ڵ�
        p = p->next;
    }

    fclose(fp);
}

int user_read_file_to_list(const char *filename, SListEntry **list)
{
    FILE *fp = NULL;
    char buff[MAXBUF] = { 0 };

    fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // ������һ�У���һ���Ǳ���
    fgets(buff, MAXBUF, fp);

    SListEntry *p;
    // ��ʼ��ȡ��������
    while (fgets(buff, MAXBUF, fp) > 0) {
        // �������ڴ�
        struct _User *user_ptr = malloc(sizeof (struct _User));
        if (!user_ptr) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        memset(user_ptr, 0, sizeof(struct _User));

        // �ӻ�������ȡ���ݵ��ṹ��
        sscanf(buff, "%s %s %s %d %d %s", user_ptr->id,
        user_ptr->username, user_ptr->gender, 
        &user_ptr->num_borrow, &user_ptr->max_num_borrow, user_ptr->passwd);

        if (user_ptr == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // ��������
        p = slist_find_data(*list, callback_check_str_id, (SListValue *)&user_ptr->id);
        // ����pΪ�յ�ʱ��Ҳ����˵���û�������
        if (p == NULL) {
            if (slist_append(list, (SListValue *)user_ptr) != NULL) {
                puts("[+] ����ɹ�\n\n");
            } else {
                puts("[-] ����ʧ��\n\n");
            }
        } else {
            puts("[-] �û��Ѵ���\n\n");
            return -1;
        }

    }

    fclose(fp);
}

void pre_welcome()
{
    puts("1:) ��½");
    puts("2:) ע��");
    puts("3:) ��������");
}

int main(int argc, char const* argv[])
{
    int input;
    // ͼ���������ڴ洢ͼ��
    SListEntry *book_list = NULL;
    // �û��������ڴ洢�û�
    SListEntry *user_list = NULL;
    struct _User *user;
    struct _User *current_user;

    user_read_file_to_list("A.txt", &user_list);
    book_read_file_to_list("B.txt", &book_list);

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
                // if (forget_passwd(&user_list)) {
                //     puts("�һ�����ɹ�");
                //     break;
                // } else {
                //     puts("�һ�����ʧ��");
                //     break;
                // }
        }

    }

login_succeed:
    while (1) {
        welcome();
        puts("");
        puts("�������ѡ��:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // if (!is_in_sll(user, user_list, callback)) {
                //     insert_user()
                // }
                if (current_user->type != TEACHER) {
                    printf("[-] ѧ���������ͼ��\n\n\n");
                    break;
                }
                // ���ͼ��
                insert_book(&book_list);
                break;
            case 2:
                if (current_user->type != TEACHER) {
                    printf("[-] ѧ������ɾ��ͼ��\n\n\n");
                    break;
                }
                // ɾ��ͼ��
                delete_book(&book_list);
                break;
            case 3:
                if (current_user->type != TEACHER) {
                    printf("[-] ѧ�������޸�ͼ��\n\n\n");
                    break;
                }
                // �޸�ͼ��
                modify_book(&book_list);
                break;
            case 4:
                // ���ü�����
                query_book(&book_list);
                break;
            case 5:
                // ���黹�飬���޸�book_list������������Ҫȡ��ַ
                borrow_book(current_user, &book_list);
                break;
            case 6:
                // ����
                return_book(current_user, &book_list);
                break;
            case 7:
                show_userinfo(current_user);
                break;
            case 8:
                // statistic(book_list);
                break;
            case 9:
                show_books(book_list);
                break;
            case 10:
                user_save_list_to_file("A.txt", user_list);
                book_save_list_to_file("B.txt", book_list);
                exit(EXIT_SUCCESS);
            default:
                puts("[-] �������\n\n");
                break;
        }
    }

    slist_free(book_list);
    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("��ӭʹ��ͼ�����ϵͳ");
    puts("1:) ���һ��ͼ��");
    puts("2:) ɾ��һ��ͼ��");
    puts("3:) �޸�һ��ͼ��");
    puts("4:) ��ѯһ��ͼ��");
    puts("5:) ����");
    puts("6:) ����");
    puts("7:) �鿴�û��軹��Ϣ");
    puts("8:) ͳ��");
    puts("9:) �鿴ʣ��ͼ��");
    puts("10:) �˳�");
    puts("-------------------");
    puts("");
}


struct _User *login(SListEntry **entry) 
{
    struct _User *new_user;
    SListEntry *p;
    SListValue *data;
    char passwd[MAXBUF] = { 0 };

    new_user = (struct _User *) malloc(sizeof(struct _User));

    puts("�������û���");
    scanf("%s", new_user->username);
    puts("����������");
    scanf("%s", new_user->passwd);

    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user);
    if (p == NULL) {
        puts("[-] �û�δע��");
        return NULL;
    } else {
        if (strncmp(((struct _User *)p->data)->passwd, new_user->passwd, 
        strlen(((struct _User *)p->data)->passwd)) == 0)
            return (struct _User *)p->data;
    }
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
    puts("����������Ա�:");
    scanf("%s", new_user->gender);
    puts("���������ְλ 0:��ʦ, 1ѧ��:");
    scanf("%d", &new_user->type);
    puts("�������û���");
    scanf("%s", new_user->username);

    while (1) 
    {
        puts("����������:");
        scanf("%s", passwd);
        puts("�����ٴ�������:");
        scanf("%s", passwd_repeat);

        if (strncmp(passwd, passwd_repeat, strlen(passwd)) == 0) {
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

// int query_book_by_id(SListEntry **entry, int id)
// {
//     SListEntry *p;
// 	SListEntry *rover;
//     SListValue *data;
// 
//     p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
//     if (p == NULL) {
//         puts("-------------------");
//         puts("δ��ѯ������");
//         puts("-------------------");
//         return -1;
//     } else {
//         data = slist_data(p);
// 
//         puts("----------------------");
//         printf("��ѯ�������\n");
//         // ������Ҫǿ��ת��
//         printf("id:%d\n", ((struct _BookInfo *)data)->id);
//         printf("����:%s\n", ((struct _BookInfo *)data)->name);
//         printf("����:%s\n", ((struct _BookInfo *)data)->author_name);
//         puts("----------------------");
//     }
//     return 1;
// }

int insert_book(SListEntry **list)
{
    BookInfo *book_info;
    SListEntry *p;

    book_info = malloc(sizeof (struct _BookInfo));
    if (book_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("�����鱾id:");
    scanf("%s", book_info->id);
    puts("�����鱾����:");
    scanf("%s", book_info->name);
    puts("�����鱾����:");
    scanf("%s", book_info->author_name);
    puts("�������������: 1)Novel 2)Classic 3)Tech");
    scanf("%d", &book_info->type);
    puts("");

    p = slist_find_data(*list, callback_check_str_id, (SListValue *)&book_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)book_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
            return 1;
        } else {
            puts("[-] ����ʧ��\n\n");
            return 0;
        }
    } else {
        puts("[-] �����Ѵ���\n\n");
        return -1;
    }
    return 1;
}

int delete_book(SListEntry **entry)
{
    int id;

    puts("����Ҫɾ���鱾��id:");
    scanf("%d", &id);
    delete_book_by_id(entry, id);

    return 1;
}

int delete_book_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _BookInfo *book_info;

    // ɾ�����������, ��һ ͼ���û�д���, �ڶ� ͼ����ж౾����(ֻ��num_left--)��
    // ���� ͼ���ֻ��һ����(��Ҫɾ���ڵ�)
    p = slist_find_data(*entry, callback_check_str_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("���鲻����");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        book_info = (struct _BookInfo *) value;
        if (slist_remove_entry(entry, p) == 0) {
            puts("[-] ɾ������ʧ��\n\n");
            return -1;
        } else {
            puts("[+] ɾ���ɹ�\n\n");
            return 1;
        }
    }
    puts("");
}

int callback_check_id(SListValue a, SListValue b)
{
    // if (((struct _BookInfo *)a)->id == *(int *)b)
    //     return 1;
    // else
    //     return 0;
}

int callback_check_str_id(SListValue a, SListValue b)
{
    if (strcmp(((struct _BookInfo *)a)->id, b) == 0)
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

int query_book(SListEntry **entry)
{
    char id[4] = { 0 };

    puts("������Ҫ��ѯ��id:");
    scanf("%s", id);
    query_book_by_id(entry, id);

    return 1;
}

int query_book_by_id(SListEntry **entry, char *id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    p = slist_find_data(*entry, callback_check_str_id, (SListValue *)&id);
    if (p == NULL) {
        puts("[-] δ��ѯ������\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("��ѯ�������\n");
        // ������Ҫǿ��ת��
        printf("id:%s\n", ((struct _BookInfo *)data)->id);
        printf("����:%s\n", ((struct _BookInfo *)data)->name);
        printf("����:%s\n", ((struct _BookInfo *)data)->author_name);
        puts("----------------------");
    }
    return 1;
}

int modify_book(SListEntry **entry)
{
    return 0;
}

int borrow_book(struct _User *user, SListEntry **book_list)
{
    char id[MAXBUF] = { 0 };
    SListEntry *book;
    SListEntry *user_book;

    puts("������Ҫ������id:");
    scanf("%s", id);

    // Ҫ����鲻���ڣ�ֱ�ӷ��ش���
    book = slist_find_data(*book_list, callback_check_str_id, (SListValue *)&id);
    if (book == NULL) {
        puts("[-] ���鲻����");
        return -1;
    }

    // puts("�������ʱ��:");
    // scanf("%d", &p->time_borrow);
    // // �������������
    // if (p->num_borrow > p->max_num_borrow) {
    //     puts("��������������");
    //     return -1;
    // }

    // ���û������в��Ҵ��飬�еĻ�ֱ��num_left++,û�еĻ��ٴ����ڵ�
    user_book = slist_find_data(user->borrowed_book, callback_check_str_id, (SListValue *)&id);
    if (!user_book) {
        // û�ҵ�
        if (!slist_append(&user->borrowed_book, book->data)) {
            puts("[-] ���ͼ���������û���������ʧ��\n\n");
            return -1;
        }
    } else {
        ((struct _BookInfo *)user_book->data)->left_num++;
    }

    // �û�Ҫ������Ҫ�ж�ͼ��ݵ����Ƿ񹻣�ͼ��ݵ��������ᷢ���仯
    // ���ͼ���ԭ���鱾���� == 1, ��ɾ���ýڵ㣬����ֻ��Ҫ������-1
    if (((struct _BookInfo *)book->data)->left_num == 1) {
        // ��ԭ�е�ͼ������ɾ������
        if (!slist_remove_entry(book_list, book)) {
            puts("[-] ɾ��ͼ��ʧ��");
            return -1;
        }
    } else {
        ((struct _BookInfo *)book->data)->left_num--;
    }


    user->num_borrow++;

    puts("[+] ����ɹ�\n\n");
    return 1;
}

int return_book(struct _User *user, SListEntry **book_list)
{
    char id[MAXBUF] = { 0 };
    SListEntry *user_entry;
    SListEntry *book_entry;

    puts("������Ҫ�������id:");
    scanf("%s", id);

    // ���û��������ҵ�����
    user_entry = slist_find_data(user->borrowed_book, callback_check_str_id, (SListValue *)&id);
    if (user_entry == NULL) {
        puts("[-] �û�δ�����\n\n");
        return -1;
    }

    // ��ͼ���������ҵ�����
    book_entry = slist_find_data(*book_list, callback_check_str_id, 
    (SListValue *)((struct _BookInfo *)user_entry->data)->id);
    // ����ҲҪ���ǻ������������ԭ��ͼ�������û�д����򴴽��ڵ㣬����ֻ��Ҫ������+1����
    if (!book_entry) {
        // ��ͼ��������δ�ҵ��ýڵ㣬���
        if (!slist_append(book_list, user_entry)) {
            puts("[-] ���û���黹ʱ����\n\n\n");
            return -1;
        }
    } else {
        ((struct _BookInfo *)book_entry->data)->left_num++;
    }

    // ͬʱ�輸��ͬ����������
    // ����û�����ͼ������������==1������û�����������ɾ������������-1
    if (((struct _BookInfo *)user_entry->data)->left_num == 1) {
        if (!slist_remove_entry(&user->borrowed_book, user_entry)) {
            puts("[-] ���û�����������ɾ������\n\n");
            return -1;
        }
    } else {
        // ����, ֻ��Ҫ��ͼ������-1����
        ((struct _BookInfo *)user->borrowed_book->data)->left_num--;
    }

    user->num_borrow--;


    puts("[+] ����ɹ�\n\n");
    return 1;
}

// ��ʼ��ѧ������ʦ��������
void teacher_borrow(struct _BookInfo *p)
{
    // p->max_num_borrow = 15;
    // p->max_time_borrow = 180;
}

void student_borrow(struct _BookInfo *p)
{
    // p->max_time_borrow = 10;
    // p->max_time_borrow = 120;
}

struct _User *ask_user_info(struct _User *p)
{
    struct _User *user;

    user = malloc(sizeof(struct _User));
    if (user == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    p = malloc(sizeof(struct _User));
    if (p == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // �����ڴ�
    memcpy(user, p, sizeof(struct _User));

    puts("����������:");
    scanf("%s", user->name);
    puts("����ѧ����:");
    scanf("%s", user->id);
    puts("��������� 0:)��ʦ, 1:)ѧ��:");
    scanf("%d", &user->type);

    return user;
}

int insert_user(SListEntry **list, SListValue *user)
{
    SListEntry *p;

    if (slist_append(list, (SListValue *)user) != NULL) {
        puts("[+] �����û��ɹ�\n\n");
        return 1;
    } else {
        puts("[-] �����û�ʧ��\n\n");
        return 0;
    }
}

void show_userinfo(struct _User *p)
{
    SListEntry *temp;

    puts("-------------------");
    printf("�û���:%s\n", p->username);
    // printf("��������:%d\n", t->num_borrow);
    printf("��������:%d\n", p->num_borrow);

    if (!p->borrowed_book) {
        puts("�û�δ���κ��鼮");
        return;
    }

    temp = p->borrowed_book;
    while (temp) {
        printf("����: %s\n", ((struct _BookInfo *)temp->data)->name);
        temp = temp->next;
    }
}

void show_books(SListEntry *book_list)
{
    SListValue *value;
    SListEntry *p = book_list;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        if (!value)
            break;

        printf("ID:%s\t", ((struct _BookInfo *) value)->id);
        printf("����:%s\t", ((struct _BookInfo *) value)->name);
        printf("����:%s\t", ((struct _BookInfo *) value)->author_name);
        puts("");

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("[-] δ��ѯ���κ�����\n\n");
    }
}

// int statistic(SListEntry *book_list)
// {
//     int id;
//     int n = 0;
//     SListEntry *p;
//     int num_borrowed, num_left;
// 
//     puts("-------------------");
//     puts("ͼ��ͳ������:");
// 
//     p = book_list;
//     while (p != NULL) {
//         id = ((struct _BookInfo *)p->data)->id;
//         num_left = ((struct _BookInfo *)p->data)->num_left;
//         num_borrowed = ((struct _BookInfo *)p->data)->num_borrowed;
// 
//         printf("�鱾id:%d ʣ������:%d ��������:%d\n", id, num_left, num_borrowed);
//         // printf("�鱾id:%d ������:%lf\n", id, ((double) num_left) / num_borrowed);
//         n++;
//         p = p->next;
//     }
//     puts("-------------------");
// 
//     if (n == 0) {
//         puts("û���κ�����");
//     }
// }
// 