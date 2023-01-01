#include "handle_ip.h"
#include "handle_tcp.h"
#include "handle_udp.h"
#include "handle_icmp.h"
#include "handle_igmp.h"
#include "handle_ether.h"
#include "appli.h"

/* Function that handles ip packets */
u_char* handle_IP(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite) {

    const struct ip* ip;
    u_int length = pkthdr->len;
    u_int hlen,version;

    int len;

    /* jump pass the ethernet header */
    ip = (struct ip*)(packet + sizeof(struct ether_header));
    length -= sizeof(struct ether_header); 

    /* check to see we have a packet of valid length */
    if (length < sizeof(struct ip))
    {
        printf("\ttruncated ip %d\n",length);
        return NULL;
    }

    len     = ntohs(ip->ip_len);
    hlen    = ip->ip_hl; /* header length */
    version = ip->ip_v;  /* ip version */

    /* check version */
    if(version != 4)
    {
      printf("\tUnknown version %d\n",version);
      return NULL;
    }

    /* check header length */
    if(hlen < 5 )
    {
        printf("\tbad-hlen %d \n",hlen);
    }

    /* see if we have as much packet as we should */
    if(length < len)
        printf("\t\ntruncated IP - %d bytes missing\n",len - length);

    u_int16_t id = ntohs(ip->ip_id);
    u_int16_t cks = ntohs(ip->ip_sum);

    /* Depending on the verbosity we print the packet differently, and we handle the packet beneath the ip header depending on the protocol used */
    switch (verbosite)
    {
        case 3:
            printf("\t----\n");
            printf("\tIP\n");
            printf("\t| Version : %d | IHL : %d | Total length : %d |\n",
                    version,hlen,len);
            printf("\t| Identification : %hu | Offset : %d |\n",
                    id,ip->ip_off);
            printf("\t| TTL : %d | ",ip->ip_ttl);

            if(ip->ip_p == 0x06){
                printf("Protocol : TCP | ");
                printf("Checksum : %hu |\n\t| ",cks);
                printf("Source address : %s |\n\t| ",inet_ntoa(ip->ip_src));
                printf("Destination address : %s |\n",inet_ntoa(ip->ip_dst));
                handle_TCP(args, pkthdr, packet,verbosite);
            }
            else if(ip->ip_p == 0x11){
                printf("Protocol : UDP | ");
                printf("Checksum : %hu |\n\t| ",cks);
                printf("Source address : %s |\n\t| ",inet_ntoa(ip->ip_src));
                printf("Destination address : %s |\n",inet_ntoa(ip->ip_dst));
                handle_UDP(args, pkthdr, packet,verbosite);
            }
            else if(ip->ip_p == 0x01){
                printf("Protocol : ICMP | ");
                printf("Checksum : %hu |\n\t| ",cks);
                printf("Source address : %s |\n\t| ",inet_ntoa(ip->ip_src));
                printf("Destination address : %s |\n",inet_ntoa(ip->ip_dst));
                handle_ICMP(args, pkthdr, packet,verbosite);
            }
            else if(ip->ip_p == 0x02){
                printf("Protocol : IGMP | ");
                printf("Checksum : %hu |\n\t| ",cks);
                printf("Source address : %s |\n\t| ",inet_ntoa(ip->ip_src));
                printf("Destination address : %s |\n",inet_ntoa(ip->ip_dst));
                handle_IGMP(args, pkthdr, packet,verbosite);
            }
            else {
                printf("Protocol : ? | ");
                printf("Checksum : %hu |\n\t| ",cks);
                printf("Source address : %s |\n\t| ",inet_ntoa(ip->ip_src));
                printf("Destination address : %s |\n",inet_ntoa(ip->ip_dst));
            }
            break;
        case 2:
            if(ip->ip_p == 0x06){
                printf("\t(IP) Version : %d  IHL : %d  Off : %d  Prot : TCP  Source : %s  Dest : %s\n",
                        version,hlen,ip->ip_off,inet_ntoa(ip->ip_src),inet_ntoa(ip->ip_dst));
                handle_TCP(args, pkthdr, packet,verbosite);
            }
            else if(ip->ip_p == 0x11){
                printf("\t(IP) Version : %d  IHL : %d  Off : %d  Prot : UDP  Source : %s  Dest : %s\n",
                        version,hlen,ip->ip_off,inet_ntoa(ip->ip_src),inet_ntoa(ip->ip_dst));
                handle_UDP(args, pkthdr, packet,verbosite);
            }
            else if(ip->ip_p == 0x01){
                printf("\t(IP) Version : %d  IHL : %d  Off : %d  Prot : ICMP  Source : %s  Dest : %s\n",
                        version,hlen,ip->ip_off,inet_ntoa(ip->ip_src),inet_ntoa(ip->ip_dst));
                handle_ICMP(args, pkthdr, packet,verbosite);
            }
            else if(ip->ip_p == 0x02){
                printf("\t(IP) Version : %d  IHL : %d  Off : %d  Prot : IGMP  Source : %s  Dest : %s\n",
                        version,hlen,ip->ip_off,inet_ntoa(ip->ip_src),inet_ntoa(ip->ip_dst));
                handle_IGMP(args, pkthdr, packet,verbosite);
            }
            else {
                printf("\t(IP) Version : %d  IHL : %d  Off : %d  Prot : ?  Source : %s  Dest : %s\n",
                        version,hlen,ip->ip_off,inet_ntoa(ip->ip_src),inet_ntoa(ip->ip_dst));
                handle_ICMP(args, pkthdr, packet,verbosite);
            }
            break;
        case 1:
            printf(" | (IP) V : %d  S : %s  D : %s",
                        version,inet_ntoa(ip->ip_src),inet_ntoa(ip->ip_dst));
            if(ip->ip_p == 0x06){handle_TCP(args, pkthdr, packet,verbosite);}
            else if(ip->ip_p == 0x11){handle_UDP(args, pkthdr, packet,verbosite);}
            else if(ip->ip_p == 0x01){handle_ICMP(args, pkthdr, packet,verbosite);}
            else if(ip->ip_p == 0x02){handle_IGMP(args, pkthdr, packet,verbosite);}
            break;
        default:
            break;
    }
    return NULL;
}



