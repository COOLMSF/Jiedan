#include <time.h>
#define MAX_LINE 1024
struct csv_data {
	char time[MAX_LINE];
	time_t raw_time;
	char dst_ip[MAX_LINE];
	char src_ip[MAX_LINE];
	char protocol[5];
	short ip_ver;
	unsigned dst_port;
	unsigned src_port;
	char flag[MAX_LINE];
};
