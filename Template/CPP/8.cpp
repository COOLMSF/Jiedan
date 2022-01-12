#include <stdio.h>
#include <stdlib.h>
#define MAXSTRLEN 255         //��󴮳�
typedef char SString[MAXSTRLEN+1];   //���Ķ���˳��洢��ʾ��0�ŵ�Ԫ��Ŵ��ĳ���
int next[MAXSTRLEN];            //KMP�㷨���õ���next����

//1. ��ģʽ��T��next����ֵ����������next
void get_next(SString T,int next[ ])   
{   // ��ģʽ��T��next����ֵ������������next
	int j=1,k=0;
	next[1]=0;
    while (j<T[0])
	{
		if (k==0 || T[k]==T[j]) 
		{
			++j; ++k; 
			if (T[j]!=T[k])  next[j]=k;
			else next[j]=next[k];
		}
		else k=next[k];
	}
}
//2. KMPƥ�亯��
int Index(SString S,SString T,int pos) 
{    // ����ģʽ��T��next������T������S�е�pos���ַ�֮���λ�õ�KMP�㷨
     // ����T�ǿգ�1 pos  StrLength(s)
	int i=pos,j=1;
	while (i<=S[0]&&j<=T[0])
	{
		if (j==0||S[i]==T[j]) {++i;++j;}  // �����ȽϺ���ַ�
		else j=next[j];                // ģʽ�������ƶ�
	}
   if (j>T[0])  return (i-T[0]);           // ƥ��ɹ�
   else return 0;                       // ƥ��ʧ��
}

//3. �󴮳�
int lenth(SString str)    
{
	int i=1;
	while(str[i]) i++;
	return(i-1);
}
//4. ���Һ���
void find(char name[],SString keys) //�ú����������������Ҫ���֣����������ÿһ��
{                                    //Ҫ���ҵĹؼ��֣��Ӵ洢�ͻ���Ϣ���ļ������ж�ȡ�ַ�������
	SString text; //��Ŵӿͻ���Ϣ�ļ���ȡ��һ���ַ���      
	int i=1,j=0,k;   //i���ڴ���кţ�j���ڴ���к�,k���������ʽ�Ŀ���
	int n=0;  //n��¼���ִ���
	FILE *fp;
	if (!(fp=(fopen(name,"r")))) //�򿪴洢�ͻ���Ϣ���ļ�
	{
		printf("Open file error!\n");
		exit(0);
	}
	keys[0]=lenth(keys);        //����lenth������ؼ��ֵĳ���
    get_next(keys,next);        //����get_next������ģʽ�����ؼ��֣�ÿһ���ַ���Ӧ��nextֵ
    printf("\n%s�����ڣ�\n",&keys[1]);    //��ӡ�ؼ���
	while (!feof(fp))        //�����û���ͻ���Ϣ�ļ�ĩβ
	{
		k=0;		
		fgets(&text[1],MAXSTRLEN,fp);     //�ӿͻ���Ϣ�ļ��ж�ȡһ���ַ���������text����
		text[0]=lenth(text);              //�����Ĵ��ĳ���
		j=Index(text,keys,j+1);        //����KMP�㷨��ͳ�ƹؼ����ڸ��г��ֵ�λ�ã���ƥ�䲻�ɹ��򷵻�0
		if (j!=0)
		{ printf("\trow=%d,\tcol=%d",i,j); k++; n++;}   //��ƥ��ɹ����ӡ�кź��к�
		while(j!=0)         //�������ҵ��˹ؼ��֣������Ѱ�ҿ��Ƿ���ƥ��ɹ�
		{
			j=Index(text,keys,j+1); //����KMP�㷨�Ӹ��ҵ����кź�һ�ַ���ƥ��
			if (j!=0)         
			{   n++;
				printf(",%d",j); } //��ƥ��ɹ������ӡ�к�
		}
		i++; //�кż�1������һ����Ѱ��
		if (k) printf("\n");  //�����ʽ��
	}
	printf("%s������%d��\n",&keys[1],n); 
}
//5. ������
int main()
{
	char name[50];   //�洢����Ŀͻ���Ϣ·���ַ���
	SString words[10];   //�����ַ������飬���ڴ洢����Ĺؼ���
	int n,i;
	printf("�������Ѵ����Ŀͻ���Ϣ�ļ���·�� (��D:\\message.txt):\n");
	scanf("%s",name);   //�û��������·�����ı��ļ���
	printf("������Ҫ���ҵĹؼ���n (n<10)��\n");
	scanf("%d",&n);  //�û�����Ҫ���ҵĹؼ��ָ���
	printf("������Ҫ���ҵı��:\n");
	for (i=0;i<n;i++)
		scanf("%s",&words[i][1]); //�û�һ��������Ҫ���ҵĹؼ��֣�words[i][0]���ڴ���ַ����ĳ���
	for (i=0;i<n;i++)
		find(name,words[i]);    //����ÿһ���ؼ��֣�����find�������в���ͳ��
	return 0; 
}
