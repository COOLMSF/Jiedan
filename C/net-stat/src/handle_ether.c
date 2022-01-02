#include "handle_ether.h"
#include <mysql.h>

extern MYSQL *conn;

/* Function handling ethernet packets (mostly every captured packet) */
void handle_ethernet(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet,int verbosite)
{
    struct ether_header *eptr;  /* net/ethernet.h */
    char buf[1024];
    char buf_src[1024];
    char buf_dst[1024];

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
            sprintf(buf_src, "%s", ether_ntoa((const struct ether_addr *)&eptr->ether_shost));
            sprintf(buf_dst, "%s", ether_ntoa((const struct ether_addr *)&eptr->ether_dhost));
	    sprintf(buf, "%s -> %s", buf_src, buf_dst);
	    write_to_database(buf, conn);
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
    return;
}

MYSQL* init_mysql()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
 
   char *server = "localhost";
   char *user = "root";
   char *password = "hushanglai"; 
   char *database = "test";
 
    conn = mysql_init(NULL);
 
   /* Connect to database */
   if (!mysql_real_connect(conn, server,
          user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   return conn;
}

int write_to_database(char *str, MYSQL *conn)
{
	char buf[1024];

	sprintf(buf, "insert into addresses values ('%s');", str);
   if (mysql_query(conn, buf)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
}
