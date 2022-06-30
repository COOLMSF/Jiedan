#include<Windows.h>
#include<iostream>
using namespace std;
const int n=4;
 
int i=0,j=0;	//i和j分别指向缓冲区
int buffer[n];	//缓冲池
int ItemP=0;	//用来存放生产的产品
int ItemC=0;	//用来存放消费的产品
 
//声明句柄
HANDLE mutex;
HANDLE empty;	
HANDLE full;	
HANDLE pThread;
HANDLE cThread;	
 
DWORD WINAPI producer(LPVOID IpParameter);
DWORD WINAPI consumer(LPVOID IpParameter);
 
int main()
{
	//创建信号量
	mutex = CreateSemaphore(NULL,1,1,NULL);
	empty = CreateSemaphore(NULL,1,4,NULL);
	full = CreateSemaphore(NULL,0,4,NULL);
 
	cout<<"市场运作开始。。。。。"<<endl;
 
	//创建线程
	pThread = CreateThread(NULL,0,producer,NULL,0,NULL);
	cThread = CreateThread(NULL,0,consumer,NULL,0,NULL);
 
	//等待相应线程结束
	WaitForSingleObject(pThread,INFINITE); 
	WaitForSingleObject(cThread,INFINITE); 
	
	
	//关闭线程句柄
	CloseHandle(pThread);
	CloseHandle(cThread);
 
	//关闭信号量句柄
	CloseHandle(mutex);
	CloseHandle(empty);
	CloseHandle(full);
 
	cout<<"结束"<<endl;
	return 0;
}
 
	//producer线程函数的定义
	DWORD WINAPI producer(LPVOID IpParameter)
	{
		for(int k=0;k<5;k++)	
		{
			cout<<"\nproducer生产一个产品"<<endl;
			ItemP=ItemP+1;			//增加一个产品
			WaitForSingleObject(empty,INFINITE);	//P操作
			WaitForSingleObject(mutex,INFINITE);
			cout<<"\n把一个产品放入了一个空的缓冲区"<<endl;
			buffer[i]=ItemP;		//将产品放入缓冲区
			i=(i+1)%n;				
			ReleaseSemaphore(mutex,1,NULL);		//V操作
			ReleaseSemaphore(full,1,NULL);
		}
		return 0;
	}
 
	DWORD WINAPI consumer(LPVOID IpParameter)
	{
		for(int k=0;k<5;k++)
		{
			WaitForSingleObject(full,INFINITE);	//P操作
			WaitForSingleObject(mutex,INFINITE);
			ItemC=buffer[j];		//将缓冲区里的产品取出，放入消费产品里头
			j=(j+1)%n;				//j指向下一个满的缓冲区
			ReleaseSemaphore(mutex,1,NULL);		//V操作
			ReleaseSemaphore(empty,1,NULL);
			cout<<"\n消费者消费一个产品"<<endl;
			ItemC=ItemC-1;			//消费一个产品
 
		}
		return 0;
	}
 

