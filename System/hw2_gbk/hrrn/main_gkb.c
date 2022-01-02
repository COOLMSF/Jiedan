#include <stdio.h>

// process�ṹ��
struct process {
	char name;
	int at, bt, ct, wt, tt;
	int completed;
	float ntt;
} p[10];

int n;

// ͨ������ʱ���������
void sortByArrival()
{
	struct process temp;
	int i, j;

    // ѡ������
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {

			if (p[i].at > p[j].at) {

                // ����
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}

void main()
{
	int i, j, t, sum_bt = 0;
	char c;
	float avgwt = 0, avgtt = 0;
	n = 5;

    // ����ʱ��
	int arriv[] = { 0, 2, 4, 6, 8 };

	// ����ʱ��
	int burst[] = { 3, 6, 4, 5, 2 };

    // ��ʼ���ṹ��
	for (i = 0, c = 'A'; i < n; i++, c++) {
		p[i].name = c;
		p[i].at = arriv[i];
		p[i].bt = burst[i];

		p[i].completed = 0;

        // ����ʱ�����
		sum_bt += p[i].bt;
	}

    // ͨ������ʱ������
	sortByArrival();
	printf("\nName\tArrival Time\tBurst Time\tWaiting Time");
	printf("\tTurnAround Time\t Normalized TT");
	for (t = p[0].at; t < sum_bt;) {

		float hrr = -9999;

		// ���ʱ���
		float temp;

		// �洢��һ�����̺�
		int loc;
		for (i = 0; i < n; i++) {

			// ����Ƿ����
			if (p[i].at <= t && p[i].completed != 1) {

                // ������Ӧ��
				temp = (p[i].bt + (t - p[i].at)) / p[i].bt;

				// �����Ӧ��
				if (hrr < temp) {

					hrr = temp;

					loc = i;
				}
			}
		}

        // ����
		t += p[loc].bt;
		// ����ȴ�ʱ��
		p[loc].wt = t - p[loc].at - p[loc].bt;
        // ������תʱ��
		p[loc].tt = t - p[loc].at;
		avgtt += p[loc].tt;
		p[loc].ntt = ((float)p[loc].tt / p[loc].bt);
        // ����״̬
		p[loc].completed = 1;

        // ����ƽ��ʱ��
		avgwt += p[loc].wt;
		printf("\n%c\t\t%d\t\t", p[loc].name, p[loc].at);
		printf("%d\t\t%d\t\t", p[loc].bt, p[loc].wt);
		printf("%d\t\t%f", p[loc].tt, p[loc].ntt);
	}
	printf("\nAverage waiting time:%f\n", avgwt / n);
	printf("Average Turn Around time:%f\n", avgtt / n);
}

