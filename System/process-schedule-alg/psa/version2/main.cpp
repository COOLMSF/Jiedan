//main.cpp
#include "PSA.h"
 
int main()
{
	std::vector<PCB> PCBList;
 
	//输入作业信息
	InputPCB(PCBList);
 
	//PSA算法
	PSA(PCBList);
 
	//显示结果
	show(PCBList);
 
	return 0;
}
 