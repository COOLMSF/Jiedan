#ifndef PSA_H_
#define PSA_H_
 
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
 
//作业结构体
typedef struct PCB
{
	int ID;							//标识符
	int Level;						//优先级
	int ComeTime;					//到达时间
	int ServerTime;					//服务时间
	int FinishTime;					//完成时间
	int TurnoverTime;				//周转时间
	double WeightedTurnoverTime;	//带权周转时间
}PCB;
 
 
/*
函数功能：输入作业信息
参数说明：
PCBList		std::vector<PCB>&		PCB链
*/
void InputPCB(std::vector<PCB> &PCBList);
 
/*
函数功能：PSA算法
参数说明：
PCBList		std::vector<PCB>&		PCB链
*/
void PSA(std::vector<PCB> &PCBList);
 
 
/*
函数功能：显示结果
参数说明：
PCBList		std::vector<PCB>&		PCB链
*/
void show(std::vector<PCB> &PCBList);
 
/*
函数功能：比较函数，用于sort()，按ComeTime升序排列
参数说明：
p1			const PCB&				PCB
p2			const PCB&				PCB
*/
bool CmpByComeTime(const PCB &p1, const PCB &p2);
 
bool CmpByLevel(const PCB &p1, const PCB &p2);
 
#endif 

void InputPCB(std::vector<PCB> &PCBList)
{
	do {
		PCB temp;
		std::cout << "input id: ";
		std::cin >> temp.ID;
		std::cout << "input priority: ";
		std::cin >> temp.Level;
		std::cout << "input arrive time: ";
		std::cin >> temp.ComeTime;
		std::cout << "input server time: ";
		std::cin >> temp.ServerTime;
		PCBList.push_back(temp);
 
		std::cout << "continue? Y/N: ";
		char ans;
		std::cin >> ans;
		if ('Y' == ans || 'y' == ans)
			continue;
		else
			break;
	} while (true);
}
 
//PSA算法
void PSA(std::vector<PCB> &PCBList)
{
	std::sort(PCBList.begin(), PCBList.end(), CmpByComeTime);		//按到达时间排序
 
	//同时到达的按优先级降序排序，决定首先运行的作业
	int i = 1;
	std::vector<PCB>::iterator it = PCBList.begin() + 1;
	while ((*it).ComeTime == (*(it - 1)).ComeTime)
	{
		++i;
		++it;
	}
	std::sort(PCBList.begin(), PCBList.begin() + i, CmpByLevel);
 
	int FinishTime = -1;
	for (it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		if ((*it).ComeTime >= FinishTime)		//没有作业正在运行，取队首作业运行
			(*it).FinishTime = (*it).ComeTime + (*it).ServerTime;
		else									//有作业正在运行，等待作业完毕，此作业再运行
			(*it).FinishTime = FinishTime + (*it).ServerTime;
		(*it).TurnoverTime = (*it).FinishTime - (*it).ComeTime;
		(*it).WeightedTurnoverTime = (double)(*it).TurnoverTime / (*it).ServerTime;
		FinishTime = (*it).FinishTime;
 
		//在一个作业运行期间，如果有其他作业到达，将他们按照优先级降序排列
		i = 1;
		while ((it + i) < PCBList.end() && (*(it + i)).ComeTime <= FinishTime)
			++i;
		std::sort(it + 1, it + i, CmpByLevel);
	}
 
	std::sort(PCBList.begin(), PCBList.end(), CmpByComeTime);		//重新排列，用于显示结果
}
 
//显示结果
void show(std::vector<PCB> &PCBList)
{
	int SumTurnoverTime = 0;
	double SumWeightedTurnoverTime = 0;
 
	std::cout.setf(std::ios::left);
 
	std::cout << std::setw(20) << "id";
	for (std::vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		std::cout << std::setw(5) << (*it).ID;
	std::cout << std::endl;
 
	std::cout << std::setw(20) << "priority";
	for (std::vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		std::cout << std::setw(5) << (*it).Level;
	std::cout << std::endl;
 
	std::cout << std::setw(20) << "arrive time";
	for (std::vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		std::cout << std::setw(5) << (*it).ComeTime;
	std::cout << std::endl;
 
	std::cout << std::setw(20) << "server time";
	for (std::vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		std::cout << std::setw(5) << (*it).ServerTime;
	std::cout << std::endl;
 
	std::cout << std::setw(20) << "finish time";
	for (std::vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
		std::cout << std::setw(5) << (*it).FinishTime;
	std::cout << std::endl;
 
	std::cout << std::setw(20) << "avg turn over time";
	for (std::vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		std::cout << std::setw(5) << (*it).TurnoverTime;
		SumTurnoverTime += (*it).TurnoverTime;;
	}
	std::cout << std::endl;
 
	std::cout << std::setw(20) << "weighted turn over time";
	for (std::vector<PCB>::iterator it = PCBList.begin(); it < PCBList.end(); ++it)
	{
		std::cout << std::setw(5) << (*it).WeightedTurnoverTime;
		SumWeightedTurnoverTime += (*it).WeightedTurnoverTime;;
	}
	std::cout << std::endl;
 
	std::cout << "avg turn over time: " << (double)SumTurnoverTime / PCBList.size() << std::endl;
	std::cout << "weighted turn over time: " << SumWeightedTurnoverTime / PCBList.size() << std::endl;
}
 
//比较函数，按ComeTime升序排列
bool CmpByComeTime(const PCB &p1, const PCB &p2)
{
	return p1.ComeTime < p2.ComeTime;
}
 
//比较函数，按Level降序排列
bool CmpByLevel(const PCB &p1, const PCB &p2)
{
	return p1.Level > p2.Level;
}