#include<stdio.h>
int main()
{
int dataString[50] = { 0 },frame[10] = { 0 };
int i = 0,j = 0,n = 0,number = 0,k = 0,is_hit = 0,counter=0;

puts("\n���뼴�������ҳ�ĳ���:");
scanf("%d",&n);
puts("\n����������:\n");
for(i=1;i<=n;i++)
scanf("%d",&dataString[i]);
puts("\n ����֡��С:");
scanf("%d",&number);

for(i=0;i<number;i++)
frame[i]= -1;
j=0;
for(i=1;i<=n;i++)
{
printf("%d\t\t",dataString[i]);
is_hit=0;
for(k=0;k<number;k++)
// hit the page
if(frame[k]==dataString[i])
is_hit=1;
if (is_hit==0)
{
frame[j]=dataString[i];
j=(j+1)%number;
counter++;
for(k=0;k<number;k++)
printf("%d\t",frame[k]);
}
printf("\n\n");
}
printf("ȱҳ����:%d",counter);
return 0;
}
