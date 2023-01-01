#include "handle_icmp.h"
#include "handle_ether.h"
#include "appli.h"

/* Function handling icmp packets */
u_char* handle_ICMP(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite)
{
    const struct icmp *icmp;
    /* We jump past the ethernet and ip headers */
    icmp = (struct icmp*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
	u_int length = pkthdr->len;
    length = length - sizeof(struct ether_header) - sizeof(struct ip);
	/* Depending on the verbosity we print the packet differently */
	switch (verbosite)
	{
		case 3:
			printf("\t\t----\n");    
			printf("\t\tICMP\n");
			printf("\t\t| Type : %hu |",icmp->icmp_type);
			printf(" Code : %hu |",icmp->icmp_code);
			printf(" Checksum : %hu |\n",icmp->icmp_cksum);
			switch (icmp->icmp_type)
			{
				case ICMP_ECHOREPLY:
					printf("\t\t| Identifier : %x |",((icmp->icmp_hun).ih_idseq).icd_id);
					printf("Sequence Number : %x |\n",((icmp->icmp_hun).ih_idseq).icd_seq);
					printf("\t\tECHO REPLY MESSAGE\n");
					break;
				case ICMP_DEST_UNREACH:
					printf("\t\t| Void : %x |\n",(icmp->icmp_hun).ih_void);
					printf("\t\tDESTINATION UNREACHABLE MESSAGE\n");
					break;
				case ICMP_SOURCE_QUENCH:
					printf("\t\t| Void : %x |\n",(icmp->icmp_hun).ih_void);
					printf("\t\tSOURCE QUENCH MESSAGE\n");
					break;
				case ICMP_REDIRECT:
					printf("\t\t| Gateway address : %s |\n",inet_ntoa((icmp->icmp_hun).ih_gwaddr));
					printf("\t\tREDIRECT MESSAGE\n");
					break;
				case ICMP_ECHO:
					printf("\t\t| Identifier : %x |",((icmp->icmp_hun).ih_idseq).icd_id);
					printf("Sequence Number : %x |\n",((icmp->icmp_hun).ih_idseq).icd_seq);
					printf("\t\tECHO MESSAGE\n");
					break;
				case ICMP_TIME_EXCEEDED:
					printf("\t\t| Void : %x |\n",(icmp->icmp_hun).ih_void);
					printf("\t\tTIME EXCEEDED MESSAGE\n");
					break;
				case ICMP_PARAMETERPROB:
					printf("\t\t| Void : %x |\n",(icmp->icmp_hun).ih_pptr);
					printf("\t\tPARAMETER PROBLEM MESSAGE\n");
					break;
				case ICMP_TIMESTAMP:
					printf("\t\t| Identifier : %x |",((icmp->icmp_hun).ih_idseq).icd_id);
					printf("Sequence Number : %x |\n",((icmp->icmp_hun).ih_idseq).icd_seq);
					printf("\t\t| Originate Timestamp : %x |\n",((icmp->icmp_dun).id_ts).its_otime);
					printf("\t\t| Receive Timestamp : %x |\n",((icmp->icmp_dun).id_ts).its_rtime);
					printf("\t\t| Transmit Timestamp : %x |\n",((icmp->icmp_dun).id_ts).its_ttime);
					printf("\t\tTIMESTAMP MESSAGE\n");
					break;
				case ICMP_TIMESTAMPREPLY:
					printf("\t\t| Identifier : %x |",((icmp->icmp_hun).ih_idseq).icd_id);
					printf("Sequence Number : %x |\n",((icmp->icmp_hun).ih_idseq).icd_seq);
					printf("\t\t| Originate Timestamp : %x |\n",((icmp->icmp_dun).id_ts).its_otime);
					printf("\t\t| Receive Timestamp : %x |\n",((icmp->icmp_dun).id_ts).its_rtime);
					printf("\t\t| Transmit Timestamp : %x |\n",((icmp->icmp_dun).id_ts).its_ttime);
					printf("\t\tTIMESTAMP REPLY MESSAGE\n");
					break;
				case ICMP_INFO_REQUEST:
					printf("\t\t| Identifier : %x |",((icmp->icmp_hun).ih_idseq).icd_id);
					printf("Sequence Number : %x |\n",((icmp->icmp_hun).ih_idseq).icd_seq);
					printf("\t\tINFO REQUEST MESSAGE\n");
					break;
				case ICMP_INFO_REPLY:
					printf("\t\t| Identifier : %x |",((icmp->icmp_hun).ih_idseq).icd_id);
					printf("Sequence Number : %x |\n",((icmp->icmp_hun).ih_idseq).icd_seq);
					printf("\t\tINFO REPLY MESSAGE\n");
					break;
				case ICMP_ADDRESS:
					printf("\t\t| Identifier : %x |",((icmp->icmp_hun).ih_idseq).icd_id);
					printf("Sequence Number : %x |\n",((icmp->icmp_hun).ih_idseq).icd_seq);
					printf("\t\t| Address Mask : %x |\n",(icmp->icmp_dun).id_mask);
					printf("\t\tADDRESS REQUEST MESSAGE\n");
					break;
				case ICMP_ADDRESSREPLY:
					printf("\t\t| Identifier : %x |",((icmp->icmp_hun).ih_idseq).icd_id);
					printf("Sequence Number : %x |\n",((icmp->icmp_hun).ih_idseq).icd_seq);
					printf("\t\t| Address Mask : %x |\n",(icmp->icmp_dun).id_mask);
					printf("\t\tADDRESS REPLY MESSAGE\n");
					break;
				default:
					break;
			}
			break;
		case 2:
			printf("\t\t(ICMP) Type : %hu  Code : %hu Checksum : %hu\n",icmp->icmp_type,icmp->icmp_code,icmp->icmp_cksum);
			break;
		case 1:
			printf(" | (ICMP) T : %hu  C : %hu |\n",icmp->icmp_type,icmp->icmp_code);
			break;
		default:
			break;
	}
    return NULL;
}
