#include "handle_arp.h"
#include "appli.h"

/* Function handling arp packets */
u_char* handle_ARP(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite) {

	const struct ether_arp* arp;
    u_int length = pkthdr->len;

    /* jump pass the ethernet header */
    arp = (struct ether_arp*)(packet + sizeof(struct ether_header));
    length -= sizeof(struct ether_header); 
    
    u_int16_t op=0,hd=0;
    op = ntohs((arp->ea_hdr).ar_op);
    hd = ntohs((arp->ea_hdr).ar_hrd);
    /* Depending on the verbosity we print the packet differently */
    switch (verbosite)
    {
        case 3:
            printf("\t----\n");
            printf("\tARP\n");
            printf("\t| Hardware type : %hu | ",hd);
            printf("Protocol type : %hu |\n",(arp->ea_hdr).ar_pro);
            printf("\t| Hardware address length : %u |",(arp->ea_hdr).ar_hln);
            printf(" Protocol address length : %u |",(arp->ea_hdr).ar_pln);
            if (op==ARPOP_REQUEST) printf(" Opcode : %hu => ARP REQUEST|\n",op);
            if (op==ARPOP_REPLY) printf(" Opcode : %hu => ARP REPLY|\n",op);
            if (op==ARPOP_RREQUEST) printf(" Opcode : %hu => RARP REQUEST|\n",op);
            if (op==ARPOP_RREPLY) printf(" Opcode : %hu => RARP REPLY|\n",op);
            if (op==ARPOP_InREQUEST) printf(" Opcode : %hu => InREQUEST|\n",op);
            if (op==ARPOP_InREPLY) printf(" Opcode : %hu => InREPLY|\n",op);
            if (op==ARPOP_NAK) printf(" Opcode : %hu => NAK|\n",op);
            printf("\t| Sender Hardware Address : %02x:%02x:%02x:%02x:%02x:%02x |\n",arp->arp_sha[0]&0xff,arp->arp_sha[1]&0xff,arp->arp_sha[2]&0xff,arp->arp_sha[3]&0xff,arp->arp_sha[4]&0xff,arp->arp_sha[5]&0xff);
            printf("\t| Sender Protocol Address : %hu.%hu.%hu.%hu |\n",arp->arp_spa[0],arp->arp_spa[1],arp->arp_spa[2],arp->arp_spa[3]);
            printf("\t| Target Hardware Address : %02x:%02x:%02x:%02x:%02x:%02x |\n",arp->arp_tha[0]&0xff,arp->arp_tha[1]&0xff,arp->arp_tha[2]&0xff,arp->arp_tha[3]&0xff,arp->arp_tha[4]&0xff,arp->arp_tha[5]&0xff);
            printf("\t| Target Protocol Address : %hu.%hu.%hu.%hu |\n",arp->arp_tpa[0],arp->arp_tpa[1],arp->arp_tpa[2],arp->arp_tpa[3]);
            break;
        case 2:
            if (op==ARPOP_REQUEST) printf("\t(ARP) Hardware type : %hu   Protocol type : %hu  Opcode : %hu => ARP REQUEST|\n",(arp->ea_hdr).ar_hrd,(arp->ea_hdr).ar_pro,op);
            if (op==ARPOP_REPLY) printf("\t(ARP) Hardware type : %hu   Protocol type : %hu  Opcode : %hu => ARP REPLY|\n",(arp->ea_hdr).ar_hrd,(arp->ea_hdr).ar_pro,op);
            if (op==ARPOP_RREQUEST) printf("\t(RARP) Hardware type : %hu   Protocol type : %hu  Opcode : %hu => RARP REQUEST|\n",(arp->ea_hdr).ar_hrd,(arp->ea_hdr).ar_pro,op);
            if (op==ARPOP_RREPLY) printf(" \t(RARP) Hardware type : %hu   Protocol type : %hu  Opcode : %hu => RARP REPLY|\n",(arp->ea_hdr).ar_hrd,(arp->ea_hdr).ar_pro,op);
            if (op==ARPOP_InREQUEST) printf("\t(ARP) Hardware type : %hu   Protocol type : %hu  Opcode : %hu => InREQUEST|\n",(arp->ea_hdr).ar_hrd,(arp->ea_hdr).ar_pro,op);
            if (op==ARPOP_InREPLY) printf("\t(ARP) Hardware type : %hu   Protocol type : %hu  Opcode : %hu => InREPLY|\n",(arp->ea_hdr).ar_hrd,(arp->ea_hdr).ar_pro,op);
            if (op==ARPOP_NAK) printf("\t(ARP) Hardware type : %hu   Protocol type : %hu  Opcode : %hu => NAK|\n",(arp->ea_hdr).ar_hrd,(arp->ea_hdr).ar_pro,op);
            break;
        case 1:
            if (op==ARPOP_REQUEST) printf(" | (ARP) REQUEST|\n");
            if (op==ARPOP_REPLY) printf(" | (ARP) REPLY|\n");
            if (op==ARPOP_RREQUEST) printf(" | (RARP) REQUEST|\n");
            if (op==ARPOP_RREPLY) printf(" | (RARP) REPLY|\n");
            if (op==ARPOP_InREQUEST) printf(" | (ARP) InREQUEST|\n");
            if (op==ARPOP_InREPLY) printf(" | (ARP) InREPLY|\n");
            if (op==ARPOP_NAK) printf(" | (ARP) NAK|\n");
            break;
        default:
            break;
    }
    return NULL;
}