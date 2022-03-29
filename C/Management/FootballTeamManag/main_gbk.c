#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAXNAME 254
#define MAXBUF 1024
#define MAXgood 100

// �ṹ��������Ϊ����
typedef struct _TeamInfo teamInfo;
typedef struct _PeopleInfo peopleInfo;
typedef void *SListValue;

// ����ṹ��
typedef struct _SListEntry SListEntry;
struct _SListEntry {
    // �����ֵ��
	SListValue data;
    // �����ָ����
	SListEntry *next;
};

// ��Ա�Ľṹ����Ϣ
struct _PeopleInfo {
    // id
    int id;
    // ����
    int age;
    char name[MAXNAME];
    char team_name[MAXNAME];
    char phone[MAXNAME];
    // λ��
    char pos[MAXNAME];
    // �Ա�
    char gender[MAXNAME];
    char comp[MAXNAME];
};

struct _TeamInfo {
    int id;
    char name[MAXNAME];
    char resp_people[MAXNAME];
    // λ��
    char pos[MAXNAME];
    SListEntry *people;
};



#define SLIST_NULL ((void *) 0)

// ����ָ�룬�û��Ƚϱ���
typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);

// ��ʾ�˵�
void welcome();
// �ͷŽڵ�
void slist_free(SListEntry *list);

// ��ӽڵ�
SListEntry *slist_append(SListEntry **list, SListValue data);

// ָ����һ���ڵ�
SListEntry *slist_next(SListEntry *listentry);

// ��ȡֵ��
SListValue slist_data(SListEntry *listentry);


// ɾ���ڵ�
int slist_remove_entry(SListEntry **list, SListEntry *entry);

// ɾ������
unsigned int slist_remove_data(SListEntry **list,
                               SListEqualFunc callback,
                               SListValue data);

// ��������
SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data);



// user inspection

// login��½�ɹ���Ӧ�÷��ص�ǰ�û�ָ�룬���򷵻�NULL
struct _Enroll *login(SListEntry **list);

// ������Ա
int insert_people(SListEntry **list);
// ɾ����Ա
int delete_team(SListEntry **list);
// ����idɾ����Ա
int delete_people_by_id(SListEntry **list, int id);
// �޸���Ա
int modify_people(SListEntry **list);
// ������Ա
int query_people(SListEntry **list);
// ��ѯid
int query_people_by_id(SListEntry **list, int id);

// �������
int insert_team(SListEntry **list);
// ɾ�����
int delete_team(SListEntry **list);
// ����idɾ�����
int delete_team_by_id(SListEntry **list, int id);
// �޸����
int modify_team(SListEntry **list);
// ��ѯ���
int query_team(SListEntry **list);
// ����id��ѯ���
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
    puts("1:) ��½");
    puts("2:) ע��");
    puts("3:) ��������");
}

int main(int argc, char const* argv[])
{
    int input;
    // ��Ա�������ڴ洢��Ա
    SListEntry *people_list = NULL;
    // ����������ڴ洢���
    SListEntry *team_list = NULL;
    // �����������ڱ�����Ϣ
    SListEntry *enroll_list = NULL;

    while (1) {
        welcome();
        puts("");
        puts("�������ѡ��:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                // �����Ա
                insert_people(&people_list);
                break;
            case 2:
                // ɾ����Ա
                delete_team(&people_list);
                break;
            case 3:
                // �޸���Ա
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
                puts("[-] �������\n\n");
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
    puts("��ӭʹ����Ա����ϵͳ");
    puts("1:) �����Ա");
    puts("2:) ɾ����Ա");
    puts("3:) �޸���Ա");
    puts("4:) ��ѯ��Ա");

    puts("5:) ������");
    puts("6:) ɾ�����");
    puts("7:) �޸����");
    puts("8:) ��ѯ���");

    puts("9:) ���ӱ�����Ϣ");
    puts("10:) ɾ��������Ϣ");
    puts("11:) �޸ı�����Ϣ");
    puts("12:) ��ѯ������Ϣ");
    puts("13:) �˳�");
    puts("-------------------");
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



// ������Ա
int insert_people(SListEntry **list)
{
    // ��Ա��Ϣ
    peopleInfo *people_info;
    SListEntry *p;

    // �����ڴ�
    people_info = malloc(sizeof (struct _TeamInfo));
    if (people_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("������Աid:");
    scanf("%d", &people_info->id);
    puts("������Ա����:");
    scanf("%s", people_info->name);
    puts("������Ա����:");
    scanf("%d", &people_info->age);
    puts("������Ա����Ա�:");
    scanf("%s", people_info->gender);
    puts("������Ա�绰:");
    scanf("%s", people_info->phone);
    puts("������Աλ��:");
    scanf("%s", people_info->pos);
    puts("������Ա�������:");
    scanf("%s", people_info->team_name);
    puts("");

    // ������Ϣ
    p = slist_find_data(*list, callback_check_id, (SListValue *)&people_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)people_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
            return 1;
        } else {
            puts("[-] ����ʧ��\n\n");
            return 0;
        }
    } else {
        puts("[-] ����Ա�Ѵ���\n\n");
        return -1;
    }
    return 1;
}

int delete_people(SListEntry **entry)
{
    int id;

    puts("����Ҫɾ����Ա��id:");
    scanf("%d", &id);
    delete_people_by_id(entry, id);

    return 1;
}

int delete_people_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _TeamInfo *people_info;

    // �ҵ��ڵ㣬����ɾ��
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("����Ա������");
        puts("-------------------");
        return -1;
    } else {
        // ��������
        value = slist_data(p);
        // �����ڴ�
        people_info = (struct _TeamInfo *) value;
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




// ��ѯ��Ա
int query_people(SListEntry **entry)
{
    int id;

    puts("������Ҫ��ѯ��id:");
    scanf("%d", &id);
    query_people_by_id(entry, id);

    return 1;
}

// ����id��ѯ��Ա
int query_people_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    // ʹ�ûص�������������Ӧid���û�
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("[-] δ��ѯ������\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("��ѯ�������\n");
        // ������Ҫǿ��ת��
        printf("id:%d\n", ((struct _PeopleInfo *)data)->id);
        printf("����:%s\n", ((struct _PeopleInfo *)data)->name);
        printf("�Ա�:%d\n", ((struct _PeopleInfo *)data)->age);
        printf("�绰:%s\n", ((struct _PeopleInfo *)data)->phone);
        printf("λ��:%s\n", ((struct _PeopleInfo *)data)->pos);
        printf("�������:%s\n", ((struct _PeopleInfo *)data)->team_name);
        puts("----------------------");
    }
    return 1;
}

int modify_people(SListEntry **entry)
{
    return 0;
}


//------------------------- ���

// �������
int insert_team(SListEntry **list)
{
    // ��Ա��Ϣ
    teamInfo *team_info;
    SListEntry *p;

    // �����ڴ�
    team_info = malloc(sizeof (struct _TeamInfo));
    if (team_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("������id:");
    scanf("%d", &team_info->id);
    puts("�������:");
    scanf("%s", team_info->name);
    puts("������ӵص�:");
    scanf("%s", team_info->pos);
    puts("������Ӹ�����:");
    scanf("%s", team_info->resp_people);
    puts("");

    p = slist_find_data(*list, callback_check_id, (SListValue *)&team_info->id);
    if (p == NULL) {
        if (slist_append(list, (SListValue *)team_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
            return 1;
        } else {
            puts("[-] ����ʧ��\n\n");
            return 0;
        }
    } else {
        puts("[-] �����\n\n");
        return -1;
    }
    return 1;
}

int delete_team(SListEntry **entry)
{
    int id;

    puts("����Ҫɾ�����id:");
    scanf("%d", &id);
    delete_team_by_id(entry, id);

    return 1;
}

int delete_team_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _TeamInfo *people_info;

    // �ҵ��ڵ㣬����ɾ��
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("����Ӳ�����");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        people_info = (struct _TeamInfo *) value;
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


// ��ѯ���
int query_team(SListEntry **entry)
{
    int id;

    puts("������Ҫ��ѯ��id:");
    scanf("%d", &id);
    query_team_by_id(entry, id);

    return 1;
}

// ����id��ѯ���
int query_team_by_id(SListEntry **entry, int id)
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
        printf("id:%d\n", ((struct _PeopleInfo *)data)->id);
        printf("����:%s\n", ((struct _PeopleInfo *)data)->name);
        printf("�Ա�:%d\n", ((struct _PeopleInfo *)data)->age);
        printf("�绰:%s\n", ((struct _PeopleInfo *)data)->phone);
        printf("λ��:%s\n", ((struct _PeopleInfo *)data)->pos);
        printf("�������:%s\n", ((struct _PeopleInfo *)data)->team_name);
        puts("----------------------");
    }
    return 1;
}

int modify_team(SListEntry **entry)
{
    return 0;
}


// ------------- ����



int insert_enroll(SListEntry **list)
{
    // ��Ա��Ϣ
    peopleInfo *people_info;
    SListEntry *p, *q;

    int people_id;
    int team_id;

    // �����ڴ�
    people_info = malloc(sizeof (struct _TeamInfo));
    if (people_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("������Աid:");
    scanf("%d", &people_info->id);
    puts("");

    puts("������Ա����:");
    scanf("%s", people_info->name);
    puts("");

    puts("����Ҫ������������:");
    scanf("%s", people_info->team_name);
    puts("");

    puts("����Ҫ����ı�������:");
    scanf("%s", people_info->comp);
    puts("");


        if (slist_append(list, (SListValue *)people_info) != NULL) {
            puts("[+] ����ɹ�\n\n");
            return 1;
        } else {
            puts("[-] ����ʧ��\n\n");
            return 0;
        }
    return 1;
}

int delete_enroll(SListEntry **entry)
{
    int id;

    puts("����Ҫɾ��������id:");
    scanf("%d", &id);
    delete_people_by_id(entry, id);

    return 1;
}

int delete_enroll_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _TeamInfo *people_info;

    // �ҵ��ڵ㣬����ɾ��
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("δ����");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        people_info = (struct _TeamInfo *) value;
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




// ��ѯ����
int query_enroll(SListEntry **entry)
{
    int id;

    puts("������Ҫ��ѯ��id:");
    scanf("%d", &id);
    query_people_by_id(entry, id);

    return 1;
}

// ����id��ѯ����
int query_enroll_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    // ��������
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("[-] δ��ѯ������\n\n");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("��ѯ�������\n");
        // ������Ҫǿ��ת��
        printf("id:%d\n", ((struct _PeopleInfo *)data)->id);
        printf("����:%s\n", ((struct _PeopleInfo *)data)->name);
        printf("�Ա�:%d\n", ((struct _PeopleInfo *)data)->age);
        printf("�绰:%s\n", ((struct _PeopleInfo *)data)->phone);
        printf("λ��:%s\n", ((struct _PeopleInfo *)data)->pos);
        printf("�������:%s\n", ((struct _PeopleInfo *)data)->team_name);
        printf("��������:%s\n", ((struct _PeopleInfo *)data)->comp);
        puts("----------------------");
    }
    return 1;
}



void slist_free(SListEntry *list)
{
	SListEntry *entry;

	entry = list;

    // ɨ������
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

    // �����ڴ�
	newentry = malloc(sizeof(SListEntry));

	if (newentry == NULL) {
		return NULL;
	}

	newentry->data = data;
	newentry->next = NULL;


	if (*list == NULL) {


		*list = newentry;

	} else {

        // ɨ�赽����ĩβ
		for (rover=*list; rover->next != NULL; rover = rover->next);
        // ��ӽڵ㵽ĩβ
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


    // �ڵ�Ϊ��
	if (*list == NULL || entry == NULL) {
		return 0;
	}

	if (*list == entry) {


		*list = entry->next;

	} else {


		rover = *list;

        // ɨ������
		while (rover != NULL && rover->next != entry) {
			rover = rover->next;
		}

		if (rover == NULL) {


			return 0;

		} else {
            // ָ����һ���ڵ�
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


    // ��������
	for (rover=list; rover != NULL; rover=rover->next) {
        // ���ûص��������
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	return NULL;
}

