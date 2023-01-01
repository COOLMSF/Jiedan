#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* HHTP key words */
#define GET { 71, 69, 84 }
#define	PUT	{ 80, 85, 84 }
#define	HEAD { 72, 69, 65, 68 }
#define	POST { 80, 79, 83, 84 }

/* SMTP key words */
#define MAIL { 77, 65, 73, 76 }
#define RCPT { 82, 67, 80, 84 }
#define DATA { 68, 65, 84, 65 }
#define EHLO { 69, 72, 76, 79 }
#define AUTH { 65, 85, 84, 72 }
#define QUIT { 81, 85, 73, 84 }
#define STARTTLS { 83, 84, 65, 82, 84, 84, 76, 83 }

/* FTP key words */
#define USER { 85, 83, 69, 82 }
#define PASS { 80, 65, 83, 83 }
#define ACCT { 65, 67, 67, 84 }
#define CWD { 67, 87, 68 }
#define CDUP { 67, 68, 85, 80 }
#define PORT { 80, 79, 82, 84 }
#define PASV { 80, 65, 83, 86 }
#define TYPE { 84, 89, 80, 69 }
#define RETR { 82, 69, 84, 82 }
#define STOR { 83, 84, 79, 82 }
#define APPE { 65, 80, 80, 69 }
#define REST { 82, 69, 83, 84 }
#define RNFR { 82, 78, 70, 82 }
#define RNTO { 82, 78, 84, 79 }
#define ABOR { 65, 66, 79, 82 }
#define DELE { 68, 69, 76, 69 }
#define RMD { 82, 77, 68 }
#define MKD { 77, 75, 68 }
#define PWD { 80, 87, 68 }
#define LIST { 76, 73, 83, 84 }
#define SITE { 83, 73, 84, 69 }
#define SYST { 83, 89, 83, 84 }
#define STAT { 83, 84, 65, 84 }
#define HELP { 72, 69, 76, 80 }
#define NOOP { 78, 79, 79, 80 }
// QUIT

/* POP key words */
#define UIDL { 85, 73, 68, 76 }
#define TOP { 84, 79, 80 }
#define LAST { 76, 65, 83, 84 }
#define RSET { 82, 83, 69, 84 }
// LIST USER PASS QUIT NOOP RETR DELE STAT 


void print_ascii(const u_char* packet, int length);
