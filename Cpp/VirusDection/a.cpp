#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char virus[200];
char DNA[200];
//BF算法
bool Index(char *S,char *T)
{
    int i=0,j=0;
    while(i<strlen(S) && j<strlen(T))
    {
        if(S[i]==T[j])
        {
            i++;j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j>=strlen(T))return true;
    else return false;
}
//字符串旋转,把病毒第一个字符变为最后一个字符
char *turn(char *T)
{
    char *temp=T;
    char tem[2]={temp[0]};
    strcpy(T,temp+1);
    strcat(T,tem);
    return T;
}
//判断DNA是否感染
bool judge(char *S,char *T)
{
    int len=strlen(T);
    for(int i=0;i<len;i++)
    {
        if(i!=0)                    //第一次病毒串不需要旋转
            strcpy(T,turn(T));
        if(Index(S,T))return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s infile outfile", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fin, *fout;

    fin = fopen(argv[1], "r");
    if (fin == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fout = fopen(argv[2], "w");
    if (fin == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int n;        
    // 读取数量
    fscanf(fin, "%d", &n);

    while(n--)
    {
       fscanf(fin, "%s %s",virus,DNA);
        //判断是否被感染
        if(judge(DNA,virus))
            fprintf(fout, "%s %s YES\n", virus, DNA);
        else
            fprintf(fout, "%s %s NO\n", virus, DNA);
    }
	return 0;
}
