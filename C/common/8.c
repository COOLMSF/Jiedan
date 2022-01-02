#include<stdio.h>
#include<stdlib.h>
int CharToDec(char c){
  if(c>='0' && c<='9') return c-'0';
  if(c>='a' && c<='f') return c-'a'+10;
  if(c>='A' && c<='F') return c-'A'+10;
  return 0;
}
int main(int argc, char *argv[]){
  char H[10];
  char *P;
  int p=1,d=0;
  printf("输入16进制数:");
  scanf("%s",H);
  for(P=H;*P;P++);
  for(P--;P>=H;P--){
    d = d + (CharToDec(*P) * p);
    p =  p*16;
  }
  printf("%d\n",d);
return 0;
}