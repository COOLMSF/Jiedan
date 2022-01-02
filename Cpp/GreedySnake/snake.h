/*     头文件     */
#include <vector> 
#include <queue> 
using namespace std; 
#ifndef SNAKE_H 
#define SNAKE_H 

class Cmap 
{
		friend class Csnake; 
		int rSign; //横坐标 
		int lSign; //纵坐标 
	public: 
	    Cmap(int r,int l){
			setPoint(r,l);
		} 
		Cmap(){} 
		void setPoint(int r,int l){
			rSign = r;
			lSign = l;
		} 
		Cmap operator-(const Cmap &m)const { 
			return Cmap(rSign - m.rSign,lSign - m.lSign); 
		} 
		Cmap operator+(const Cmap &m)const { 
			return Cmap(rSign + m.rSign,lSign + m.lSign); 
		} 
}; 

const int maxSize = 5; //初始蛇身长度 

class Csnake 
{ 
		Cmap firstSign;     //蛇头坐标 
		Cmap secondSign;    //蛇颈坐标 
		Cmap lastSign;      //蛇尾坐标 
		Cmap nextSign;      //预备蛇头 
		Cmap firstSign2;	//自动蛇头坐标
		Cmap secondSign2;   //自动蛇颈坐标 
		Cmap lastSign2;     //自动蛇尾坐标 
		Cmap nextSign2;     //自动预备蛇头 
		int row;            //列数 
		int line;           //行数 
		int count;          //蛇身长度 
		int count2;			//自动蛇身长度

		vector<vector<char> > snakeMap;     //整个游戏界面 
		queue<Cmap> MySnake;                //我的蛇
		queue<Cmap> autoSnake;				//电脑控制的自动蛇
	public: 
		//获取指定坐标点上的字符
		char getSymbol(const Cmap& c)const{              
			return snakeMap[c.lSign][c.rSign]; 
		} 
		//初始化游戏界面大小
		Csnake(int n) {                             
			if(n < 20)
				line = 20+2; 
			else if(n > 30)
				line = 30+2; 
			else 
				line = n+2; 
			row = line*3+2; 
		} 
		// 判断是否到达边界，如果到了则判断失败
		bool isDead(const Cmap& cmp) {
			return ( getSymbol(cmp)=='X' || cmp.rSign == row-1 || cmp.rSign== 0 || cmp.lSign == line-1 || cmp.lSign == 0 ||getSymbol(cmp)=='c'||getSymbol(cmp)=='='); 
		} 
		int GetDirections()const;   //从键盘获取方向键，分别为“上”“下”“左”“右”键
		void InitInstance();        //初始化游戏界面 
		bool UpdataGame();          //更新游戏界面 
		void ShowGame();            //显示游戏界面 
		bool autoDecision(int r, int l);		//电脑蛇自动控制方向
}; 
#endif // SNAKE_H 
