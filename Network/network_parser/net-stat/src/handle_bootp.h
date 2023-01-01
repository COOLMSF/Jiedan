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

#define MAGIC { 99, 130, 83, 99 }
#define FIN 0xff

u_char* handle_BOOTP(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite);
