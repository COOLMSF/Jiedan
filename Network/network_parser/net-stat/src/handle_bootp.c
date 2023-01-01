#include "bootp.h"
#include "handle_ether.h"
#include "handle_ip.h"
#include "handle_udp.h"
#include "handle_bootp.h"
#include "appli.h"

/* Function handling bootp and dhcp packets */
u_char* handle_BOOTP(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite) {
    const struct bootp* bootp;
    u_int length = pkthdr->len;

    /* jump past the ethernet, ip and udp headers */
    bootp = (struct bootp*)(packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));
    length = length - sizeof(struct ether_header) - sizeof(struct ip) - sizeof(struct udphdr);
    /* check that the remaining packet size is enough */
    if (length < sizeof(struct udphdr)) {
        printf("\t\t\ttruncated bootp\n");
    }
    /* Depending on the verbosity we print the packet differently */
    switch (verbosite)
    {
        case 3:
            printf("\t\t\t----\n");
            printf("\t\t\tBOOTP\n");
            printf("\t\t\t| Opcode : %x ",bootp->bp_op);
            printf("| Hardware type : %x ",bootp->bp_htype);
            printf("| Hardware address length : %u",bootp->bp_hlen);
            printf("| Hop count : %u |\n",bootp->bp_hops);
            printf("\t\t\t| Transaction ID : ");
            printf("%" PRIu32 " |\n",bootp->bp_xid);
            printf("\t\t\t| Number of seconds : %d |\n",bootp->bp_secs);
            printf("\t\t\t| Client IP addr : %s |\n",inet_ntoa(bootp->bp_ciaddr));
            printf("\t\t\t| Your IP addr : %s |\n",inet_ntoa(bootp->bp_yiaddr));
            printf("\t\t\t| Server IP addr : %s |\n",inet_ntoa(bootp->bp_siaddr));
            printf("\t\t\t| Gateway IP addr : %s |\n",inet_ntoa(bootp->bp_giaddr));
            printf("\t\t\t| Client Hardware addr : %s |\n",bootp->bp_chaddr);
            printf("\t\t\t| Server Host name : %s |\n",bootp->bp_sname);
            printf("\t\t\t| Boot filename : %s |\n",bootp->bp_file);
            printf("\t\t\t| Vendor specific :\n");
            break;
        case 2:
            printf("\t\t\t(BOOTP) Opcode : %u   Hardware type : %u   Your IP@ : %s  Server IP@ : %s  Boot file : %s\n",
                    bootp->bp_op,bootp->bp_htype,inet_ntoa(bootp->bp_yiaddr),inet_ntoa(bootp->bp_siaddr),bootp->bp_file);
            break;
        case 1:
            printf(" | (BOOTP) Opcode : %hu  YIP@ : %s  File : %s |",bootp->bp_op,inet_ntoa(bootp->bp_yiaddr),bootp->bp_file);
            break;
        default:
            break;
    }

    u_char cookie[]= MAGIC;
    int i=0,j=0,dhcp=0,count=0;
    int taillevend = sizeof(bootp->bp_vend);
    while (i<taillevend-4) {
        for (j=0;j<4;j++){
            if (bootp->bp_vend[i+j]==cookie[j]){
                count++;
            }
        }
        count=0;
        i++;
    }
    i=4;
    /* We check that we have a dhcp type packet */
    if(dhcp){
        /* Depending on the verbosity we print the packet differently */
        switch(verbosite)
        {
            case 3:
                printf("\t\t\t\t----\n");
                printf("\t\t\t\tDHCP\n");
                int taille=0;
                while(bootp->bp_vend[i] != FIN){
                    j=0;
                    switch(bootp->bp_vend[i])
                    {
                        case 01:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("subnet mask : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 02:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("time offset : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 03:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("router : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 06:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("DNS : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 12:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("host name : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 15:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("domain name : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 28:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("broadcast address : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 44:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("netBios over TCP/IP nameserver : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 47:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("netBios over TCP/IP scope : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 50:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("requested IP address : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 51:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("lease time : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 53:
                            i+=2;
                            switch(bootp->bp_vend[i]){
                                case 01:
                                    printf("\t\t\t\tdiscover\n");
                                    break;
                                case 02:
                                    printf("\t\t\t\toffer\n");
                                    break;
                                case 03:
                                    printf("\t\t\t\trequest\n");
                                    break;
                                case 05:
                                    printf("\t\t\t\tack\n");
                                    break;
                                case 07:
                                    printf("\t\t\t\trelease\n");
                                    break;
                                default:
                                    printf("\n");
                                    break;
                            }
                            break;
                        case 54:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("server identifier : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        case 55:
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            printf("\t\t\t\t");
                            while(j<taille){
                                printf("parameter request list : ");
                                printf("%x ",bootp->bp_vend[i+j]);
                                j++;
                            }
                            printf("\n");
                            break;
                        default:
                            printf("\t\t\t\toption non supportée\n");
                            i+=2;
                            taille=bootp->bp_vend[i-1];
                            break;
                    }
                    i+=taille;
                }
                break;
            case 2:
                printf("\t\t\t\t(DHCP)\n");
                break;
            case 1:
                printf(" | (DHCP)\n");
        }
    }
    return NULL;
}
