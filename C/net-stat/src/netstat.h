#ifndef NETSTAT_H_INCLUDED
#define NETSTAT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <ctype.h>
#include <unistd.h>
#include "handle_ether.h"

extern long unsigned int total_syn_pkt;
extern long unsigned int total_size;
extern long unsigned int total_size_thread;
extern MYSQL *conn;

void callback_ETHER(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet);
int main(int argc, char **argv);
#endif
