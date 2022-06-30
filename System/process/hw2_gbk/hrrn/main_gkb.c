#include <stdio.h>

// process结构体
struct process {
	char name;
	int at, bt, ct, wt, tt;
	int completed;
	float ntt;
} p[10];

int n;

// 通过到达时间进行排序
void sortByArrival()
{
	struct process temp;
	int i, j;

    // 选择排序
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {

			if (p[i].at > p[j].at) {

                // 交换
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

    // 到达时间
	int arriv[] = { 0, 2, 4, 6, 8 };

	// 运行时间
	int burst[] = { 3, 6, 4, 5, 2 };

    // 初始化结构体
	for (i = 0, c = 'A'; i < n; i++, c++) {
		p[i].name = c;
		p[i].at = arriv[i];
		p[i].bt = burst[i];

		p[i].completed = 0;

        // 运行时间求和
		sum_bt += p[i].bt;
	}

    // 通过到达时间排序
	sortByArrival();
	printf("\nName\tArrival Time\tBurst Time\tWaiting Time");
	printf("\tTurnAround Time\t Normalized TT");
	for (t = p[0].at; t < sum_bt;) {

		float hrr = -9999;

		// 比率变量
		float temp;

		// 存储下一个进程号
		int loc;
		for (i = 0; i < n; i++) {

			// 检查是否完成
			if (p[i].at <= t && p[i].completed != 1) {

                // 计算响应比
				temp = (p[i].bt + (t - p[i].at)) / p[i].bt;

				// 最高响应比
				if (hrr < temp) {

					hrr = temp;

					loc = i;
				}
			}
		}

        // 更新
		t += p[loc].bt;
		// 计算等待时间
		p[loc].wt = t - p[loc].at - p[loc].bt;
        // 计算周转时间
		p[loc].tt = t - p[loc].at;
		avgtt += p[loc].tt;
		p[loc].ntt = ((float)p[loc].tt / p[loc].bt);
        // 更新状态
		p[loc].completed = 1;

        // 计算平均时间
		avgwt += p[loc].wt;
		printf("\n%c\t\t%d\t\t", p[loc].name, p[loc].at);
		printf("%d\t\t%d\t\t", p[loc].bt, p[loc].wt);
		printf("%d\t\t%f", p[loc].tt, p[loc].ntt);
	}
	printf("\nAverage waiting time:%f\n", avgwt / n);
	printf("Average Turn Around time:%f\n", avgtt / n);
}

