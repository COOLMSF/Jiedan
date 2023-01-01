#include "netstat.h"
#include "handle_tcp.h"
#include <pthread.h>
#include <pcap/pcap.h>
#include <unistd.h>
#include <string.h>

int verbosite;
/* 
 * Global variable
 * This is critical region use in careful
 */
long unsigned int total_syn_pkt = 0;
long unsigned int total_size = 0;
long unsigned int total_size_thread = 0;

/* Callback function used by pcap */
void callback_ETHER(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
	/* Should these variable be locked? */
	total_size += pkthdr->len;
	total_size_thread += pkthdr->len;
    /* handle the ethernet header */
    handle_ethernet(args,pkthdr,packet,verbosite);
}

/* Main program function */
int main(int argc, char **argv)
{
	int iflag = 0;
	/* sflag for bpf filter */
	int sflag = 0;
	int vflag = 0;
	int oflag = 0;
	char *ivalue = NULL;
	char *svalue = NULL;
	char *vvalue = NULL;
	char *ovalue = NULL;
	int c;
	pthread_t thread_check_bandwidth;
	pthread_t thread_check_flood;

	/* Verify which options are used */
	while ((c = getopt (argc, argv, "i:s:v:o:")) != -1)
    	switch (c)
      	{
		case 'i':
			iflag = 1;
			ivalue = optarg;
			break;
		case 's':
			sflag = 1;
			svalue = optarg;
			break;
		case 'v':
			vflag = 1;
			vvalue = optarg;
			break;
		case 'o':
			oflag = 1;
			ovalue = optarg;
			break;
		case '?':
		    if (optopt == 'i')
		      fprintf (stderr, "Option -%c requires an argument.\n", optopt);
		    else if (isprint (optopt))
		      fprintf (stderr, "Unknown option `-%c'.\n", optopt);
		    else
		      fprintf (stderr,
		               "Unknown option character `\\x%x'.\n",
		               optopt);

			if (optopt == 'p')
				fprintf(stderr, "Option -%c retuires an integer.\n", optopt);
			else if (isprint (optopt))
		      fprintf (stderr, "Unknown option `-%c'.\n", optopt);
		    else
		      fprintf (stderr,
		               "Unknown option character `\\x%x'.\n",
		               optopt);

			if (optopt == 'v')
		      fprintf (stderr, "Option -%c requires an argument.\n", optopt);
		    else if (isprint (optopt))
		      fprintf (stderr, "Unknown option `-%c'.\n", optopt);
		    else
		      fprintf (stderr,
		               "Unknown option character `\\x%x'.\n",
		               optopt);

			if (optopt == 'o')
		      fprintf (stderr, "Option -%c requires an argument.\n", optopt);
		    else if (isprint (optopt))
		      fprintf (stderr, "Unknown option `-%c'.\n", optopt);
		    else
		      fprintf (stderr,
		               "Unknown option character `\\x%x'.\n",
		               optopt);

		    return 1;
		default:
			break;
	}
    /* INTIALISATION*/
	char *dev; /* name of the device to use */
	char *net; /* dot notation of the network address */
	char *mask;/* dot notation of the network mask */
	int ret; /* return code */
	char errbuf[PCAP_ERRBUF_SIZE];
	bpf_u_int32 netp; /* ip */
	bpf_u_int32 maskp;/* subnet mask */
	struct in_addr addr;

	u_char* args = NULL;
	pcap_t* descr;

	/* ask pcap to find a valid device for use to sniff on */
	if (!iflag){
		dev = pcap_lookupdev(errbuf);
	}
	else {
		dev = ivalue;
	}

	/* If we don't use the verbosity option, the default value is 3 */
	if (!vflag){
		verbosite = 3;
	}

	else {
		switch(atoi(vvalue))
		{
			case 1:
				verbosite=1;
				break;
			case 2:
				verbosite=2;
				break;
			case 3:
				verbosite=3;
				break;
			default:
				break;
		}
	}
	/* error checking */
	if(dev == NULL)
	{
		printf("%s\n",errbuf);
		exit(1);
	}
	/* print out device name */
	printf("DEV: %s\n",dev);

	/* ask pcap for the network address and mask of the device */
	ret = pcap_lookupnet(dev,&netp,&maskp,errbuf);
	if(ret == -1)
	{
		printf("%s\n",errbuf);
		exit(1);
	}
	
	/* get the network address in a human readable form */
	addr.s_addr = netp;
	net = inet_ntoa(addr);
	if(net == NULL)
	{
		perror("inet_ntoa");
		exit(1);
	}
	printf("NET: %s\n",net);
	
	/* do the same as above for the device's mask */
	addr.s_addr = maskp;
	mask = inet_ntoa(addr);

	if(mask == NULL)
	{
		perror("inet_ntoa");
		exit(1);
	}

	printf("MASK: %s\n",mask);
	
	/* open the device for sniffing */
	if (!oflag){
		descr = pcap_open_live(dev, BUFSIZ, 1, 10000, errbuf);
	}
	else{
		descr = pcap_open_offline(ovalue, errbuf);
	}

	if (descr == NULL)
	{
		printf("pcap_open_live() : %s\n", errbuf);
		exit(1);
	}

	/* analyze with bpf */
	if (svalue != NULL) {
		char *filter_expr = svalue;
		struct bpf_program filter;

		pcap_compile(descr, &filter, filter_expr, 0, netp);
		pcap_setfilter(descr, &filter);
		pcap_loop(descr, 0, callback_ETHER, args);
		fprintf(stdout,"\nFinished\n");

		return 0;
	}

	/* analyze without bpf */
	pcap_loop(descr,0,callback_ETHER,args);
	fprintf(stdout,"\nFinished\n");

	return 0;
} 
