#include "handle_ether.h"
#include "handle_arp.h"
#include "handle_ip.h"
#include "appli.h"

/* Function handling ethernet packets (mostly every captured packet) */
void handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite)
{
    struct ether_header *eptr;  /* net/ethernet.h */

    eptr = (struct ether_header *) packet;
    printf("-----------\n");
	printf("-----------\n");
    /* Depending on the verbosity we print the packet differently */
    switch (verbosite)
    {
        case 3:
            printf("Ethernet\n");
            printf(" | source: %s "
                    ,ether_ntoa((const struct ether_addr *)&eptr->ether_shost));
            printf("| destination: %s |\n"
                    ,ether_ntoa((const struct ether_addr *)&eptr->ether_dhost));
            break;
        case 2:
            printf("(ETH) Source : %s   Destination : %s\n",
                ether_ntoa((const struct ether_addr *)&eptr->ether_shost),
                ether_ntoa((const struct ether_addr *)&eptr->ether_dhost));
            break;
        case 1:
            printf("| (ETH) S: %s D: %s",
                ether_ntoa((const struct ether_addr *)&eptr->ether_shost),
                ether_ntoa((const struct ether_addr *)&eptr->ether_dhost));
            break;
        default:
            break;
    }
    /* check to see if we have an ip packet */
    if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
    {
        handle_IP(args,pkthdr,packet,verbosite);
    }
    /* check to see if we have an ARP packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
    {
        handle_ARP(args,pkthdr,packet,verbosite);
    }
    /* check to see if we have a REVARP packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_REVARP)
    {
        printf("(RARP)\n");
    }
    /* Check to see if we have a PUP packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_PUP)
    {
        printf("(PUP)\n");
    }
    /* Check to see if we have a SPRITE packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_SPRITE)
    {
        printf("(SPRITE)\n");
    }
    /* Check to see if we have a AT packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_AT)
    {
        printf("(AT)\n");
    }
    /* Check to see if we have a AARP packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_AARP)
    {
        printf("(AARP)\n");
    }
    /* Check to see if we have a VLAN packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_VLAN)
    {
        printf("(VLAN)\n");
    }
    /* Check to see if we have a IPX packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_IPX)
    {
        printf("(IPX)\n");
    }
    /* Check to see if we have a IPV6 packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_IPV6)
    {
        printf("(IPV6)\n");
    }
    /* Check to see if we have a LOOPBACK packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_LOOPBACK)
    {
        printf("(LOOPBACK)\n");
    }
    /* Check to see if we have a TRAIL packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_TRAIL)
    {
        printf("(TRAIL)\n");
    }
    /* Check to see if we have a NTRAIL packet */
    else  if (ntohs (eptr->ether_type) == ETHERTYPE_NTRAILER)
    {
        printf("(NTRAIL)\n");
    }
    /* Check to see if we have a packet of which we don't recognize the ethertype */
    else  if (ntohs (eptr->ether_type) == 0x88cc)
    {
        printf("(LLDP)\n");
    }
    /* Check to see if we have a */
    else  if (ntohs (eptr->ether_type) == 0x8808)
    {
        printf("(Eth Flow Control)\n");
    }
    /* Check to see if we have a */
    else  if (ntohs (eptr->ether_type) == 0x0842)
    {
        printf("(Wake-on-LAN)\n");
    }
    /* Check to see if we have a */
    else  if (ntohs (eptr->ether_type) == 0x22f3)
    {
        printf("(TRILL Protocol)\n");
    }
    /* Check to see if we have a */
    else  if (ntohs (eptr->ether_type) == 0x88a2)
    {
        printf("(ATA over Ethernet)\n");
    }
    /* Check to see if we have a */
    else  if (ntohs (eptr->ether_type) == 0x88a4)
    {
        printf("(EtherCAT Protocol)\n");
    }
    /* Check to see if we have a */
    else {
        printf("? Ethertype : 0x%04x\n",eptr->ether_type);
    }
    printf("\n");

    return;
}
