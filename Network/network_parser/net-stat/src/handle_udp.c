#include "handle_udp.h"
#include "handle_bootp.h"
#include "handle_ether.h"
#include "handle_ip.h"
#include "handle_dns.h"
#include "appli.h"


/* Function handling UDP headers */
u_char* handle_UDP(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite) {
    const struct udphdr* udp;
    u_int length = pkthdr->len;

    /* jump past the ethernet and ip headers */
    udp = (struct udphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
    length = length - sizeof(struct ether_header) - sizeof(struct ip);
    /* check that the remaining packet size is enough */
    if (length < sizeof(struct udphdr)) {
        printf("\t\ttruncated udp\n");
    }

    /* Put back the port number bytes in the right order */
    u_int16_t s=0,d=0,cks;
    s = ntohs((u_int16_t)udp->uh_sport);
    d = ntohs((u_int16_t)udp->uh_dport);
    cks = ntohs((u_int16_t)udp->uh_sum);
    
    /* Depending on the verbosity we print the packet differently */
    switch (verbosite)
    {
        case 3:
            printf("\t\t----\n");
            printf("\t\tUDP\n");
            printf("\t\t| Port Source : %d |",s);
            printf("Port Destination : %d |\n",d);
            printf("\t\t| Taille : %d |",udp->uh_ulen);
            printf("Checksum : %d |\n",cks);
            break;
        case 2:
            printf("\t\t(UDP) PSource : %hu  PDest : %hu  Taille : %hu\n",s,d,udp->uh_ulen);
            break;
        case 1:
            printf(" | (UDP) PS : %hu  PD : %hu\n",s,d);
            break;
        default:
            break;
    }

    /* We check what kind of packet is beneath the UDP header */
    if((d == 67)||(d == 68)){
        handle_BOOTP(args, pkthdr, packet,verbosite);
    }
    if((s == 53)||(s == 53)){
        handle_DNS(args, pkthdr, packet,verbosite,0);
    }
    return NULL;
}

