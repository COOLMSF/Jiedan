/*���������� */
#include <iostream> 
#include "snake.h" 
#include <windows.h> 
using namespace std; 

int main() 
{ 
	int noDead; 
    // ��ʼ��ʵ��
	Csnake s(20); 
	s.InitInstance(); 
	do { s.ShowGame(); 
		noDead=s.UpdataGame(); 
	}while (noDead);
	system("pause"); 
}
