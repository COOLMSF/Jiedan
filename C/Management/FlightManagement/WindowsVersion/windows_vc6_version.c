#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

#define MAXBUF 1024


struct _Flight {
	int id;
	char startTime[MAXBUF];
    char stopTime[MAXBUF];
    double price;
};

typedef void *SListValue;
typedef struct _SListEntry SListEntry;
struct _SListEntry {
	SListValue data;
	SListEntry *next;
};

typedef struct _Flight FlightInfo;
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
    if (((struct _Flight *)a)->id == *(int *)b)
        return 1;
    else
        return 0;
}

void welcome()
{
    puts("");
    puts("-------------------");
    puts("��ӭʹ�ú������ϵͳ");
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

int insert_flight(SListEntry **list)
{
    FlightInfo *flight_info = NULL;


    flight_info = malloc(sizeof (struct _Flight));
	memset(flight_info, 0, sizeof(struct _Flight));
    if (flight_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }



    puts("����id:");
    scanf("%d", &flight_info->id);
    puts("���뺽�࿪ʼʱ��:");
    scanf("%s", flight_info->startTime);
    puts("���뺽�ൽ��ʱ��:");
    scanf("%s", flight_info->stopTime);
    puts("���뺽��۸�:");
    scanf("%lf", &flight_info->price);

    if (slist_append(list, (SListValue *)flight_info) != NULL) {
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

int delete_flight_by_id(SListEntry **entry, int id)
{
    SListEntry *p;
    SListValue *value;
    struct _Flight *flight_info;

    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("���಻����");
        puts("-------------------");
        return -1;
    } else {
        value = slist_data(p);
        flight_info = (struct _Flight *) value;

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

int delete_flight(SListEntry **entry)
{
    int id;

    puts("����Ҫɾ����id:");
    scanf("%d", &id);
    delete_flight_by_id(entry, id);

    return 1;
}

int query_flight_by_id(SListEntry **entry, int id)
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
        printf("id:%d\n", ((struct _Flight *)data)->id);
        printf("��ʼʱ��:%s\n", ((struct _Flight *)data)->startTime);
		printf("����ʱ��:%s\n", ((struct _Flight *)data)->stopTime);
		printf("��Ʊ�۸�:%lf\n", ((struct _Flight *)data)->price);
        puts("----------------------");
    }
    return 1;
}

int query_flight(SListEntry **entry)
{
    int id;

    puts("������Ҫ��ѯ�����id:");
    scanf("%d", &id);
    query_flight_by_id(entry, id);

    return 1;
}


int modify_flight(SListEntry **entry)
{
    int id;
    SListEntry *p;

    puts("������id:");
    scanf("%d", &id);
    p = slist_find_data(*entry, callback_check_id, (SListValue *)&id);
    if (p == NULL) {
        puts("-------------------");
        puts("��Ϣ������");
        puts("-------------------");
        return -1;
    } else {

    FlightInfo *flight_info = NULL;
    flight_info = malloc(sizeof (struct _Flight));
	memset(flight_info, 0, sizeof(struct _Flight));
    if (flight_info == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    puts("�����µ�id:");
    scanf("%d", &flight_info->id);
    puts("�����µĿ�ʼʱ��:");
    scanf("%s", flight_info->startTime);
    puts("�����µĵ���ʱ��:");
    scanf("%s", flight_info->stopTime);
    puts("�����µļ۸�:");
    scanf("%lf", &flight_info->price);
    puts("");

        p->data = flight_info;

        puts("�޸ĳɹ�");
    }
}

void show_flight_table(SListEntry **flightList)
{
    SListValue *value;
    SListEntry *p = *flightList;

    int n = 0;
    puts("-------------------");
    while (p != NULL) {
        value = p->data;

        puts("----------------------");
        printf("��ѯ�������\n");
        // ������Ҫǿ��ת��
        printf("id:%d\n", ((struct _Flight *)value)->id);
        printf("��ʼʱ��:%s\n", ((struct _Flight *)value)->startTime);
		printf("����ʱ��:%s\n", ((struct _Flight *)value)->stopTime);
		printf("�۸�:%lf\n", ((struct _Flight *)value)->price);
		
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

void save_file(SListEntry **flightList)
{
    SListValue *value;
    SListEntry *p = *flightList;
	FILE *fp;

	char filename[1000] = { 0 };

	puts("�����ļ�����");
	scanf("%s", filename);

	fp = fopen(filename, "w");


   
    while (p != NULL) {
        value = p->data;

        fprintf(fp,"id:%d\n", ((struct _Flight *)value)->id);
        fprintf(fp,"��ʼʱ��:%s\n", ((struct _Flight *)value)->startTime);
		fprintf(fp,"����ʱ��:%s\n", ((struct _Flight *)value)->stopTime);
		fprintf(fp, "�۸�:%lf\n", ((struct _Flight *)value)->price);
        fprintf(fp,"\n");

        p = p->next;
      
    }

	puts("�����ļ��ɹ�");
}


int main(int argc, char const* argv[])
{
    int input;
    SListEntry *flightList = NULL;
    

    while (1) {
        welcome();
        puts("");
        puts("�������ѡ��:");
        scanf("%d", &input);

        switch (input) {
            case 1:
                insert_flight(&flightList);
                break;
            case 2:
                modify_flight(&flightList);
                break;
            case 3:
                query_flight(&flightList);
                break;
            case 4:
                show_flight_table(&flightList);
                break;
			case 5:
				delete_flight(&flightList);
				break;
			case 6:
				save_file(&flightList);
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
