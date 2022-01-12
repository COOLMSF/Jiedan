#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <inttypes.h>
#include <ctype.h>
#include <unistd.h>
#include <mysql.h>

MYSQL* init_mysql();
int write_to_database(char *str, MYSQL *conn);
void handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite);
