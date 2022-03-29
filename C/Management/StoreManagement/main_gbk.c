#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAXNAME 254
#define MAXBUF 1024
#define MAXgood 100

struct _TeamInfo {
    int id;
    char name[MAXNAME];
    char sell_date[MAXNAME];
    int ntotal;
    int nsell;
    double price;
};
typedef struct _TeamInfo teamInfo;
typedef void *SListValue;

typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};


#define SLIST_NULL ((void *) 0)

typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);



struct _Enroll {
    char id[4];
    int num_borrow;
    char name[MAXNAME];
    char username[MAXNAME];
    char passwd[MAXBUF];
    SListEntry *buied_goods;
    enum { ADMIN, USER } type;
};

void welcome();
void pre_welcome();
void slist_free(SListEntry *list);

SListEntry *slist_append(SListEntry **list, SListValue data);

SListEntry *slist_next(SListEntry *listentry);

SListValue slist_data(SListEntry *listentry);


int slist_remove_entry(SListEntry **list, SListEntry *entry);
unsigned int slist_remove_data(SListEntry **list,
                               SListEqualFunc callback,
                               SListValue data);

SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data);



// user inspection

// login��½�ɹ���Ӧ�÷��ص�ǰ�û�ָ�룬���򷵻�NULL
struct _Enroll *login(SListEntry **list);
int regist(SListEntry **list);
int forget_passwd(SListEntry **list);

int insert_enroll(SListEntry **list);
int delete_team(SListEntry **list);
int delete_team_by_id(SListEntry **list, int id);
int modify_people(SListEntry **list);
int query_people(SListEntry **list);
int query_people_by_id(SListEntry **list, int id);
int buy_good(struct _Enroll *user, SListEntry *good_list);
int callback_check_id(SListValue a, SListValue b);
int callback_check_username(SListValue a, SListValue b);
int insert_user(SListEntry **list, SListValue *value);
void show_userinfo(struct _Enroll *p);
void show_people(SListEntry *good_list);


void pre_welcome()
{
    puts("1:) ��½");
    puts("2:) ע��");
    puts("3:) ��������");
}

int main(int argc, char const* argv[])
{
    int input;
    // ��Ʒ���������ڴ洢��Ʒ
    SListEntry *good_list = NULL;
    // �û����������ڴ洢�û�
    SListEntry *user_list = NULL;
    struct _Enroll *user;
    struct _Enroll *current_user;

    while (1) {
        pre_welcome();
        puts("�������ѡ��:");
        scanf("%d", &input);

        switch (input) 
        {
            if (input > 2) {
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
                if (current_user->type != ADMIN) {
                    printf("[-] �û�����������Ʒ\n\n\n");
                    break;
                }
                // ������Ʒ
                insert_enroll(&good_list);
                break;
            case 2:
                if (current_user->type != ADMIN) {
                    printf("[-] �û�����ɾ����Ʒ\n\n\n");
                    break;
                }
                // ɾ����Ʒ
                delete_team(&good_list);
                break;
            case 3:
                if (current_user->type != ADMIN) {
                    printf("[-] �û������޸���Ʒ\n\n\n");
                    break;
                }
                // �޸���Ʒ
                modify_people(&good_list);
                break;
            case 4:
                // ���ü������
                query_people(&good_list);
                break;
            case 5:
                buy_good(current_user, good_list);
                break;
            case 6:
                show_userinfo(current_user);
                break;
            case 7:
                show_people(good_list);
                break;
            case 8:
                exit(EXIT_SUCCESS);
            default:
                puts("[-] �������\n\n");
                break;
        }
    }

    slist_free(good_list);
    return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("��ӭʹ����Ʒ����ϵͳ");
    puts("1:) ����һ����Ʒ");
    puts("2:) ɾ��һ����Ʒ");
    puts("3:) �޸�һ����Ʒ");
    puts("4:) ��ѯһ����Ʒ");
    puts("5:) ������Ʒ");
    puts("6:) �鿴�û�������Ϣ");
    puts("7:) �鿴ʣ����Ʒ");
    puts("8:) �˳�");
    puts("-------------------");
    puts("");
}

// ��¼����
struct _Enroll *login(SListEntry **entry) 
{
    // �û��ṹ�壬���ڴ洢�µ��û�����
    struct _Enroll *new_user;
    SListEntry *p;
    SListValue *data;

    // �����ڴ�
    new_user = (struct _Enroll *) malloc(sizeof(struct _Enroll));

    // ��ȡ�û���Ϣ
    puts("�������û���");
    scanf("%s", new_user->username);
    puts("����������:");
    scanf("%s", new_user->passwd);

    // �������������Ƿ��и��û�
    p = slist_find_data(*entry, callback_check_username, (SListValue *)new_user);
    if (p == NULL) {
        puts("[-] �û�δע��");
        return NULL;
    } else {
        data = slist_data(p);
        // ����û���
        if (strcmp(((struct _Enroll *)data)->username, new_user->username) == 0 &&
        // ����û�����
        strcmp(((struct _Enroll *)data)->passwd, new_user->passwd) == 0) {
            return (struct _Enroll *)p->data;
        }
    }
    puts("[-] �˺Ż��������");
    return NULL;
}

// ע�ắ��
int regist(SListEntry **entry)
{
    struct _Enroll *new_user;
    SListEntry *p;
    SListValue *data;
    char passwd[MAXBUF], passwd_repeat[MAXBUF];

    // �����ڴ�
    new_user = (struct _Enroll *)malloc(sizeof(struct _Enroll));

    // �����û���Ϣ
    puts("������id:");
    scanf("%s", new_user->id);
    puts("�������������:");
    scanf("%s", new_user->name);
    puts("������������� 0:����Ա, 1:�û�:");
    scanf("%d", &new_user->type);
    puts("�������û���");
    scanf("%s", new_user->username);

    while (1) 
    {
        puts("����������:");
        scanf("%s", passwd);
        puts("�����ٴ�������:");
        scanf("%s", passwd_repeat);

        // �Ƚ���������
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

// ������Ʒ
int insert_enroll(SListEntry **list)
{
    // ��Ʒ��Ϣ
    teamInfo *good_info;
    SListEntry *p;

    // �����ڴ�
    good_info = malloc(sizeof (struct _TeamInfo));
    if (good_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("������Ʒid:");
    scanf("%d", &good_info->id);
    puts("������Ʒ����:");
    scanf("%s", good_info->name);
    puts("������Ʒ�۸�:");
    scanf("%lf", &good_info->price);
    puts("������Ʒ����:");
    scanf("%d", &good_info->ntotal);
    puts("");

    p = slist_find_data(*list, callback_check_id, (SListValue *)&good_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)good_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
            return 1;
        } else {
            puts("[-] ����ʧ��\n\n");
            return 0;
        }
    } else {
        puts("[-] ����Ʒ�Ѵ���\n\n");
        return -1;
    }
    return 1;
}

int delete_team(SListEntry **entry)
{
    int id;

    puts("����Ҫɾ����Ʒ��id:");
    scanf("%d", &id);
    delete_team_by_id(entry, id);

    return 1;
}

int delete_team_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _TeamInfo *good_info;

    // �ҵ��ڵ㣬����ɾ��
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("����Ʒ������");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        good_info = (struct _TeamInfo *) value;
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

// ���id�Ļص�����
int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _TeamInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

// ����û����Ļص�����
int callback_check_username(SListValue a, SListValue b)
{
    if (strcmp(((struct _Enroll *)a)->username, ((struct _Enroll *)b)->username) == 0)
        return 1;
    else
        return 0;
}

// ��ѯ��Ʒ
int query_people(SListEntry **entry)
{
    int id;

    puts("������Ҫ��ѯ��id:");
    scanf("%d", &id);
    query_people_by_id(entry, id);

    return 1;
}

// ����id��ѯ��Ʒ
int query_people_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("[-] δ��ѯ������\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("��ѯ�������\n");
        // ������Ҫǿ��ת��
        printf("id:%d\n", ((struct _TeamInfo *)data)->id);
        printf("��Ʒ��:%s\n", ((struct _TeamInfo *)data)->name);
        printf("�۸�:%lf\n", ((struct _TeamInfo *)data)->price);
        puts("----------------------");
    }
    return 1;
}

int modify_people(SListEntry **entry)
{
    return 0;
}

int buy_good(struct _Enroll *user, SListEntry *good_list)
{
    int id;
    SListEntry *good;

    puts("������Ҫ�������Ʒ��id:");
    scanf("%d", &id);

    good = slist_find_data(good_list, callback_check_id, (SListValue *)&id);
    if (good == NULL) {
        puts("[-] ����Ʒ������");
        return -1;
    }
    // ��Ʒ��������+1
    ((teamInfo *)good->data)->nsell++;

    // ����Ʒ������ �û��Ĺ�����Ʒ����֮��
    if (!slist_append(&user->buied_goods, good->data)) {
        puts("[-] ������Ʒ�������û�������Ʒ����ʧ��\n\n");
        return -1;
    }

    puts("[+] ������Ʒ�ɹ�\n\n");
    return 1;
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

void show_userinfo(struct _Enroll *p)
{
    SListEntry *temp;

    puts("-------------------");
    printf("�û���:%s\n", p->name);
    // printf("����������:%d\n", t->num_borrow);
    printf("����������:%d\n", p->num_borrow);

    if (!p->buied_goods) {
        puts("�û�δ�����κ���Ʒ");
        return;
    }

    temp = p->buied_goods;
    while (temp) {
        printf("��Ʒ��: %s\n", ((struct _TeamInfo *)temp->data)->name);
        temp = temp->next;
    }
}

void show_people(SListEntry *good_list)
{
    SListValue *value;
    SListEntry *p = good_list;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        if (!value)
            break;

        printf("ID:%d\t", ((struct _TeamInfo *) value)->id);
        printf("��Ʒ��:%s\t", ((struct _TeamInfo *) value)->name);
        printf("��Ʒ�۸�:%lf\t", ((struct _TeamInfo *) value)->price);
        printf("��Ʒ������:%d\t", ((struct _TeamInfo *) value)->ntotal);
        printf("��Ʒ��������:%d\t", ((struct _TeamInfo *) value)->nsell);
        puts("");

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("[-] δ��ѯ���κ�����\n\n");
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


SListEntry *slist_next(SListEntry *listentry)
{
	return listentry->next;
}

int slist_remove_entry(SListEntry **list, SListEntry *entry)
{
	SListEntry *rover;

	/* If the list is empty, or entry is NULL, always fail */

	if (*list == NULL || entry == NULL) {
		return 0;
	}

	/* Action to take is different if the entry is the first in the list */

	if (*list == entry) {

		/* Unlink the first entry and update the starting pointer */

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

	/* Free the list entry */

	free(entry);

	/* Operation successful */

	return 1;
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

