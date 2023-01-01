#include "handle_tcp.h"
#include "handle_ip.h"
#include "handle_ether.h"
#include "csv.h"
#include <string.h>
#include <time.h>
#include "netstat.h"

/* Function handling tcp packets  */
u_char* handle_TCP(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite) {
    const struct tcphdr* tcp;
	/* Why not iphdr? */
	const struct ip* ip;
    u_int length = pkthdr->len;

	/* write struct to file */
	FILE *fp;
	struct csv_data csv;

	/*
	 * We should write the field name when the program firstly runs
	 */
	if(access("data.csv", F_OK) != 0) {
	}

	/* append csv file */
	fp = fopen("data.csv", "a+");

    /* jump past the ethernet and ip headers */
	ip = (struct ip*)(packet + sizeof(struct ether_header));
    tcp = (struct tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
    length = length - sizeof(struct ether_header) - sizeof(struct ip);
    /* check that the remaining packet size is enough */
    if (length < sizeof(struct tcphdr)) {
        printf("\t\ttruncated tcp\n");
    }
	
	// save time
	time_t raw_time;
	struct tm *time_info;
	char *time_str = NULL;

	time(&raw_time);
	// save raw time to calculate the time difference
	csv.raw_time = raw_time;
	time_info = localtime(&raw_time);
	// asctime will append a new line at the end of the string
	// we don't need it
	time_str = asctime(time_info);
	*(time_str + strlen(time_str) - 1) = '\0';

	strcpy(csv.time, time_str);

	// save ip
	strcpy(csv.src_ip, inet_ntoa(ip->ip_src));
	strcpy(csv.dst_ip, inet_ntoa(ip->ip_dst));

	// save protocol
    if(ip->ip_p == 0x06){
        strcpy(csv.protocol, "TCP");
    }
    else if(ip->ip_p == 0x11){
		strcpy(csv.protocol, "UDP");
    }
    else if(ip->ip_p == 0x01){
		strcpy(csv.protocol, "ICMP");
    }
    else if(ip->ip_p == 0x02){
		strcpy(csv.protocol, "IGMP");
    }

	// save ip version
	csv.ip_ver = ip->ip_v;

	// save port
	csv.src_port = tcp->th_sport;
	csv.dst_port = tcp->th_dport;

    /* Depending on the verbosity we print the packet differently
	 * Only verbosite 3 will log flag
	 */
	strcpy(csv.flag, "");
    switch (verbosite)
    {
        case 3:
            printf("\t\t----\n");
            printf("\t\tTCP\n");
            printf("\t\tPort source : %hu\n",ntohs(tcp->th_sport));
            printf("\t\tPort destination : %hu\n",ntohs(tcp->th_dport));
            printf("\t\tSequence Number : ");
            printf("%d\n",ntohl(tcp->th_seq));
            printf("\t\tAcknowledgment Number : ");
            printf("%d\n",ntohl(tcp->th_ack));
            printf("\t\tOffset : %d\n",tcp->th_off);

            printf("\t\tMessage type : ");
            if (tcp->th_flags & TH_URG) {
                printf("URG ");
				strcat(csv.flag, "URG");
            }
            if (tcp->th_flags & TH_ACK) {
                printf("ACK ");
				strcat(csv.flag, "ACK");
            }
            if (tcp->th_flags & TH_PUSH) {
                printf("PUSH ");
				strcat(csv.flag, "PUSH");
            }
            if (tcp->th_flags & TH_RST) {
                printf("RST ");
				strcat(csv.flag, "RST");
            }
            if (tcp->th_flags & TH_SYN) {
				total_syn_pkt++;
				puts("!!!");
				printf("%ld\n", total_syn_pkt);
                printf("SYN ");
				strcat(csv.flag, "SYN");
            }
            if (tcp->th_flags & TH_FIN) {
                printf("FIN ");
				strcat(csv.flag, "FIN");
            }
            printf("\t\t\n");

            printf("\t\tWindow size : %d\n",ntohs(tcp->th_win));
            printf("\t\tChecksum : %d\n",ntohs(tcp->th_sum));
            printf("\t\tUrgent pointer : %hu\n",tcp->th_urp);
            break;
        case 2:
            printf("\t\t(TCP) PSource : %hu  PDestination : %hu  Seq num : %d  Ack num : %d\n",
                tcp->th_sport,tcp->th_dport,tcp->th_seq,tcp->th_ack);
            break;
        case 1:
            printf(" | (TCP) PS : %hu  PD : %hu  SN : %d",
                tcp->th_sport,tcp->th_dport,tcp->th_seq);
            break;
        default:
            break;
    }

	fclose(fp);
    return NULL;
}

