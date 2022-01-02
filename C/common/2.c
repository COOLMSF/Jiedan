#include <stdio.h>
#include <time.h>
int main()
{
    //get local time

    struct tm *local;
    time_t t;
    t=time(NULL);
    local=localtime(&t);
    int n[4];
    n[1]=local->tm_hour;
    n[2]=local->tm_min;
    n[3]=local->tm_sec;       
    printf("%d:%d:%d\n",n[1],n[2],n[3]);

    //initialization electron watch time display

    char display(int i);
    char time[10][8];
    int i,j;

    for (i=0; i<10; i++)
    {
        time[i][1] = time[i][4] = time[i][7] = '-';
        time[i][3] = time[i][2] = time[i][6] = time[i][5] = '|';
    }
    for (i=0; i<10; i++)
        switch (i)
        {
        case 0:time[i][4] = ' ';break;
        case 1:time[i][1] = time[i][2] = time[i][7] = time[i][4] = time[i][5] = ' ';break;
        case 2:time[i][2] = time[i][6] = ' ';break;
        case 3:time[i][5] = time[i][2] = ' ';break;
        case 4:time[i][5] = time[i][1] = time[i][7] = ' ';break;
        case 5:time[i][3] = time[i][5] = ' ';break;
        case 6:time[i][3] = ' ';break;
        case 7:time[i][4] = time[i][2] = time[i][5] = time[i][7] = ' ';break;
        case 8:break;
        case 9:time[i][5] = ' ';break;
    }                                     

    //display time in electronic watch

    for (i=0; i<8; i++)
    {
        if (i==1 || i==4 || i==7)
            for (j=1; j<4; j++)
                if (n[j]<10)
                    printf(" %c  %c  ",time[0][i], time[n[j]][i]);
                else if (n[j]==10)
                    printf(" %c  %c  ",time[1][i], time[0][i]);
                else 
                    printf(" %c  %c  ",time[n[j]/10][i], time[n[j]%10][i]);
        if (i==2 || i==5)
            for (j=1; j<4; j++)
            {
                if ( n[j] < 10 )
                    printf("%c %c%c %c",time[0][i], time[0][i+1], time[n[j]][i], time[ n[j] ][i+1]);
                else if (n[j]==10)
                    printf("%c %c%c %c",time[1][i], time[1][i+1], time[0][i], time[0][i+1]);
                else 
                    printf("%c %c%c %c",time[n[j]/10][i], time[n[j]/10][i+1], time[ n[j]%10 ][i], time[ n[j]%10 ][i+1]);
                if (j!=3)
                    putchar('*');
            }
        if (i==3 || i==6)
            continue;
        printf("\n");
    }                                                                
    return 0;
}
