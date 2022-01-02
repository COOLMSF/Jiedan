/*主函数部分 */
#include <iostream> 
#include "snake.h" 
#include <windows.h> 
using namespace std; 

int main() 
{ 
	int noDead; 
    // 初始化实例
	Csnake s(20); 
	s.InitInstance(); 
	do { s.ShowGame(); 
		noDead=s.UpdataGame(); 
	}while (noDead);
	system("pause"); 
}
