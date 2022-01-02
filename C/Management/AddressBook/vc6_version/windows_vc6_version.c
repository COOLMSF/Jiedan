#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

#define MAXBUF 1024
// ��ţ����ظ������������Ա𣬼�ͥ�绰���ƶ��绰��������λ��
// ��ϵ��ַ����������

struct _PersonInfo {
	int id;
	char name[MAXBUF];
    char gender[MAXBUF];
	char telephone[MAXBUF];
	char mobile_phone[MAXBUF];
	char company[MAXBUF];
	char address[MAXBUF];
	char mail[MAXBUF];
};

typedef void *SListValue;
typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};

#define SLIST_NULL ((void *) 0)
typedef struct _PersonInfo PersonInfo;
typedef int (*SListCompareFunc)(SListValue value1, SListValue value2);
typedef int (*SListEqualFunc)(SListValue value1, SListValue value2);

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
		for (rover=*list; rover->next != NULL; rover = rover->next);
		rover->next = newentry;
	}

	return newentry;
}

SListValue slist_data(SListEntry *listentry)
{
	return listentry->data;
}

int slist_remove_entry(SListEntry **list, SListEntry *entry)
{
	SListEntry *rover;

	if (*list == NULL || entry == NULL) {
		return 0;
	}

	if (*list == entry) {

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

	free(entry);

	return 1;
}

unsigned int slist_remove_data(SListEntry **list, SListEqualFunc callback,
                               SListValue data)
{
	SListEntry **rover;
	SListEntry *next;
	unsigned int entries_removed;

	entries_removed = 0;

	rover = list;

	while (*rover != NULL) {


		if (callback((*rover)->data, data) != 0) {

			next = (*rover)->next;
			free(*rover);
			*rover = next;

			++entries_removed;
		} else {

			rover = &((*rover)->next);
		}
	}

	return entries_removed;
}


SListEntry *slist_find_data(SListEntry *list,
                            SListEqualFunc callback,
                            SListValue data)
{
	SListEntry *rover;

	for (rover=list; rover != NULL; rover=rover->next) {
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	/* Not found */

	return NULL;
}

int callback_check_id(SListValue a, SListValue b)
{
    if (((struct _PersonInfo *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("��ӭʹ��ͨѶ¼����ϵͳ");
    puts("1:) �����Ϣ");
    puts("2:) �޸���Ϣ");
    puts("3:) ��ѯ��Ϣ");
    puts("4:) �г�������Ϣ");
    puts("5:) ɾ����Ϣ");
	puts("6:) �����ļ�");
    puts("7:) �˳�");
    puts("-------------------");
    puts("");
}

int insert_person(SListEntry **list)
{
    PersonInfo *person_info = NULL;


    person_info = malloc(sizeof (struct _PersonInfo));
	memset(person_info, 0, sizeof(struct _PersonInfo));
    if (person_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }



    puts("����id:");
    scanf("%d", &person_info->id);
    puts("��������:");
    scanf("%s", person_info->name);
    puts("�����Ա�:");
    scanf("%s", person_info->gender);
    puts("�����ͥ�绰:");
    scanf("%s", person_info->telephone);
    puts("�����ƶ��绰:");
    scanf("%s", person_info->mobile_phone);
    puts("���빫˾��ַ:");
    scanf("%s", person_info->company);
    puts("�����ͥ��ַ:");
	scanf("%s", person_info->address);
	puts("�����ʼ�:");
	scanf("%s", person_info->mail);
    puts("");

    if (slist_append(list, (SListValue *)person_info) != NULL) {
        puts("----------------------");
        puts("����ɹ�");
        puts("----------------------");
        return 1;
    } else {
        puts("----------------------");
        puts("����ʧ��");
        puts("----------------------");
        return 0;
    }
}

int delete_person_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _PersonInfo *person_info;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("��ϵ�˲�����");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        person_info = (struct _PersonInfo *) value;

        if (slist_remove_entry(entry, p) == 0) {
            puts("-------------------");
            puts("ɾ������ʧ��");
            puts("-------------------");
            return -1;
        } else {
            puts("-------------------");
            puts("ɾ�����ݳɹ�");
            puts("-------------------");
            return 1;
        }
    }
    puts("");
}

int delete_person(SListEntry **entry)
{
    int id;

    puts("����Ҫɾ������ϵ�˵�id:");
    scanf("%d", &id);
    delete_person_by_id(entry, id);

    return 1;
}

int query_person_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
	SListEntry *rover;
    SListValue *data;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("δ��ѯ������");
        puts("-------------------");
        return -1;
    } else {
        data = slist_data(p);

        puts("----------------------");
        printf("��ѯ�������\n");
        // ������Ҫǿ��ת��
        printf("id:%d\n", ((struct _PersonInfo *)data)->id);
        printf("��ϵ������:%s\n", ((struct _PersonInfo *)data)->name);
		printf("��ϵ���Ա�:%s\n", ((struct _PersonInfo *)data)->gender);
		printf("��ϵ�˵绰:%s\n", ((struct _PersonInfo *)data)->mobile_phone);
		printf("��ϵ�˼�ͥ�绰:%s\n", ((struct _PersonInfo *)data)->telephone);
		printf("��ϵ���Ա�:%s\n", ((struct _PersonInfo *)data)->gender);
		printf("��ϵ��˾��ַ:%s\n", ((struct _PersonInfo *)data)->company);
		printf("��ϵ�˼�ͥסַ:%s\n", ((struct _PersonInfo *)data)->address);
		printf("��ϵ������:%s\n", ((struct _PersonInfo *)data)->mail);
        puts("----------------------");
    }
    return 1;
}

int query_person(SListEntry **entry)
{
    int id;

    puts("������Ҫ��ѯ��id:");
    scanf("%d", &id);
    query_person_by_id(entry, id);

    return 1;
}


int modify_person(SListEntry **entry)
{
    int id;
    SListEntry *p;

    puts("������id:");
    scanf("%d", &id);
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("��ϵ�˲�����");
        puts("-------------------");
        return -1;
    } else {

    PersonInfo *person_info = NULL;
    person_info = malloc(sizeof (struct _PersonInfo));
	memset(person_info, 0, sizeof(struct _PersonInfo));
    if (person_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("�����µ�id:");
    scanf("%d", &person_info->id);
    puts("�����µ�����:");
    scanf("%s", person_info->name);
    puts("�����µ��Ա�:");
    scanf("%s", person_info->gender);
    puts("�����µļ�ͥ�绰:");
    scanf("%s", person_info->telephone);
    puts("�����µ��ƶ��绰:");
    scanf("%s", person_info->mobile_phone);
    puts("�����µĹ�˾��ַ:");
    scanf("%s", person_info->company);
    puts("�����µļ�ͥ��ַ:");
	scanf("%s", person_info->address);
	puts("�����µ��ʼ�:");
	scanf("%s", person_info->mail);
    puts("");

        p->data = person_info;

        puts("�޸ĳɹ�");
    }
}

void show_person_table(SListEntry **deviceList)
{
    SListValue *value;
    SListEntry *p = *deviceList;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        puts("----------------------");
        printf("��ѯ�������\n");
        // ������Ҫǿ��ת��
        printf("id:%d\n", ((struct _PersonInfo *)value)->id);
        printf("��ϵ������:%s\n", ((struct _PersonInfo *)value)->name);
		printf("��ϵ���Ա�:%s\n", ((struct _PersonInfo *)value)->gender);
		printf("��ϵ�˵绰:%s\n", ((struct _PersonInfo *)value)->mobile_phone);
		printf("��ϵ�˼�ͥ�绰:%s\n", ((struct _PersonInfo *)value)->telephone);
		printf("��ϵ���Ա�:%s\n", ((struct _PersonInfo *)value)->gender);
		printf("��ϵ��˾��ַ:%s\n", ((struct _PersonInfo *)value)->company);
		printf("��ϵ�˼�ͥסַ:%s\n", ((struct _PersonInfo *)value)->address);
		printf("��ϵ������:%s\n", ((struct _PersonInfo *)value)->mail);
        puts("----------------------");
        printf("\n");

        p = p->next;
        n++;
    }
    puts("-------------------");

    if (n == 0) {
        puts("-------------------");
        puts("δ��ѯ���κ�����");
        puts("-------------------");
    }
}

void save_file(SListEntry **deviceList)
{
    SListValue *value;
    SListEntry *p = *deviceList;
	FILE *fp;

	char filename[1000] = { 0 };

	puts("�����ļ�����");
	scanf("%s", filename);

	fp = fopen(filename, "w");


   
    while (p != NULL) {
        value = p->data;

        fprintf(fp,"id:%d\n", ((struct _PersonInfo *)value)->id);
        fprintf(fp,"��ϵ������:%s\n", ((struct _PersonInfo *)value)->name);
		fprintf(fp,"��ϵ���Ա�:%s\n", ((struct _PersonInfo *)value)->gender);
		fprintf(fp, "��ϵ�˵绰:%s\n", ((struct _PersonInfo *)value)->mobile_phone);
		fprintf(fp,"��ϵ�˼�ͥ�绰:%s\n", ((struct _PersonInfo *)value)->telephone);
		fprintf(fp,"��ϵ���Ա�:%s\n", ((struct _PersonInfo *)value)->gender);
		fprintf(fp,"��ϵ��˾��ַ:%s\n", ((struct _PersonInfo *)value)->company);
		fprintf(fp,"��ϵ�˼�ͥסַ:%s\n", ((struct _PersonInfo *)value)->address);
		fprintf(fp,"��ϵ������:%s\n", ((struct _PersonInfo *)value)->mail);
        fprintf(fp,"\n");

        p = p->next;
      
    }

	puts("�����ļ��ɹ�");
}


int main(int argc, char const* argv[])
{
    int input;
    SListEntry *deviceList = NULL;
    struct _PersonInfo *device;

    while (1) {
        welcome();
        puts("");
        puts("�������ѡ��:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                insert_person(&deviceList);
                break;
            case 2:
                modify_person(&deviceList);
                break;
            case 3:
                query_person(&deviceList);
                break;
            case 4:
                show_person_table(&deviceList);
                break;
			case 5:
				delete_person(&deviceList);
				break;
			case 6:
				save_file(&deviceList);
				break;
            case 7:
                exit(EXIT_SUCCESS);
            default:
                puts("-------------------");
                puts("�������");
                puts("-------------------");
                break;
        }
    }
    return 0;
}
