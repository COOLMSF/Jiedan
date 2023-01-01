#include "handle_tcp.h"
#include "handle_ip.h"
#include "handle_ether.h"
#include "handle_http.h"
#include "handle_telnet.h"
#include "handle_dns.h"
#include "handle_smtp.h"
#include "handle_ftp.h"
#include "handle_pop.h"
#include "handle_imap.h"
#include "appli.h"
#include "csv.h"
#include <string.h>
#include <time.h>
#include "netstat.h"

int check_net_bandwidth(void)
{
	// struct pcap_pkthdr *p;
	// p = (struct pcap_pkthdr *)ptr;

	/*
	 * check total_size every 10 second
	 */
	while (1) {
		long unsigned int rate = total_size_thread / 10;
		sleep(10);
		if (rate <= 1000) {
			printf("Bandwidth:%ldB/s\n", rate);
		} else {
			printf("Bandwidth:%ldKB/s\n", rate / 1000);
		}
		/* 
		 * reset tital_size_thread after use, this variable just stores
		 * the total traffic of 10 seconds
		 */
		total_size_thread = 0;
	}
}

int check_syn_flood(void)
{
	while (1) {
		int start_syn_pkt;
		int end_syn_pkt;

		start_syn_pkt = total_syn_pkt;
		// check every 5 seconds
		sleep(5);
		end_syn_pkt = total_syn_pkt;

		if (((end_syn_pkt - start_syn_pkt) / 5) > 10) {
			time_t raw_time;
			struct tm *time_info;
			char *time_str;
			FILE *f;
			char line[BUFSIZ];

			time(&raw_time);
			time_info = localtime(&raw_time);
			time_str = asctime(time_info);
			*(time_str + strlen(time_str) - 1) = '\0';
			sprintf(line, "syn flood attack at %s\n", time_str);
			f = fopen("warning.txt", "a+");
			fwrite(line, strlen(line), 1, f);
			fclose(f);
		}
	}
}

void write_csv(FILE *fp, struct csv_data csv)
{
	char buf[MAX_LINE];
	char num_str[MAX_LINE];

	sprintf(num_str, "%ld", csv.raw_time);
	sprintf(buf, "%s, %s, %s, %s, %d, %d, %s, %s, %d\n", \
		csv.time, num_str, csv.dst_ip, csv.src_ip, csv.dst_port, csv.src_port, \
		csv.flag, csv.protocol, csv.ip_ver);
	fwrite(buf, strlen(buf), 1, fp);
}

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

	// write to file
	write_csv(fp, csv);
	fclose(fp);

    /* We check what kind of packet is beneath the tcp header */
    if  (((ntohs(tcp->th_dport) == 80) || (ntohs(tcp->th_sport) == 80)) && (length - sizeof(struct tcphdr) > 0)) {
        handle_HTTP(args,pkthdr,packet,verbosite);
    }else if (((ntohs(tcp->th_dport) == 23) || (ntohs(tcp->th_sport) == 23)) && (length - sizeof(struct tcphdr) > 0)) {
        handle_TELNET(args,pkthdr,packet,verbosite);
    }else if (((ntohs(tcp->th_dport) == 53) || (ntohs(tcp->th_sport) == 53)) && (length - sizeof(struct tcphdr) > 0)) {
        handle_DNS(args,pkthdr,packet,verbosite,1);
    }else if (((ntohs(tcp->th_dport) == 25) || (ntohs(tcp->th_sport) == 25)) && (length - sizeof(struct tcphdr) > 0)) {
        handle_SMTP(args,pkthdr,packet,verbosite);
    }else if (((ntohs(tcp->th_dport) == 587) || (ntohs(tcp->th_sport) == 587)) && (length - sizeof(struct tcphdr) > 0)) {
        printf(" (Ciphered SMTP)\n");
    }else if (((ntohs(tcp->th_dport) == 465) || (ntohs(tcp->th_sport) == 465)) && (length - sizeof(struct tcphdr) > 0)) {
        printf(" (SMTP with SSL)\n");
    }else if (((ntohs(tcp->th_dport) == 20) || (ntohs(tcp->th_sport) == 20)) && (length - sizeof(struct tcphdr) > 0)) {
        handle_FTP(args,pkthdr,packet,verbosite);
    }else if (((ntohs(tcp->th_dport) == 21) || (ntohs(tcp->th_sport) == 21)) && (length - sizeof(struct tcphdr) > 0)) {
        handle_FTP(args,pkthdr,packet,verbosite);
    }else if (((ntohs(tcp->th_dport) == 143) || (ntohs(tcp->th_sport) == 143)) && (length - sizeof(struct tcphdr) > 0)) {
        handle_IMAP(args,pkthdr,packet,verbosite);
    }else if (((ntohs(tcp->th_dport) == 110) || (ntohs(tcp->th_sport) == 110)) && (length - sizeof(struct tcphdr) > 0)) {
        handle_POP(args,pkthdr,packet,verbosite);
    }
    return NULL;
}

