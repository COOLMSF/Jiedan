#include <windows.h> 
#include <ctime> 
#include <iostream> 
#include "snake.h" 
using namespace std; 

int rr;
int ll;
bool isDead;
void Csnake::InitInstance() { 
	// snakeMap[竖坐标][横坐标] 
	snakeMap.resize(line); 
	// 画出world的边界或者蛇可以移动的地图
	for(int i = 0; i < line; i++) { 
		snakeMap[i].resize(row); 
		for(int j = 0; j < row; j++) { 
			if( i == 0 || i == line-1 || j == 0 || j == row-1)
				snakeMap[i][j] = '=';
			else
				snakeMap[i][j] = ' '; 
		} 
	}

	for(int m = 1;m < maxSize+1; m++) { 
		//初始蛇身 
		snakeMap[line/2][m] = 'X'; 
		//将蛇身坐标压入队列 
		MySnake.push(Cmap(m,(line/2))); 

		snakeMap[line/3][m] = 'c'; 
		autoSnake.push(Cmap(m,(line/3)));
	}

	//链表头尾
	firstSign = MySnake.back(); 
	secondSign.setPoint(maxSize-1,line/2); 

	firstSign2 = autoSnake.back();
	secondSign2.setPoint(maxSize-1,line/3);
} 
int Csnake::GetDirections()const { 
	if(GetKeyState(VK_UP)<0)        //1表示按下上键 
		return 1; 
	if(GetKeyState(VK_DOWN)<0)		//2表示按下下键 
		return 2; 
	if(GetKeyState(VK_LEFT)<0)		//3表示按下左键 
		return 3; 
	if(GetKeyState(VK_RIGHT)<0)		//4表示按下右键
		return 4;  
	return 0; 
}
bool Csnake::autoDecision(int r, int l) {
    // 这个函数参考大佬的
	bool eatFood = true;
	bool turn1 = false;
	bool turn2 = false;
	if( firstSign2.rSign > r) {
		if( (firstSign2.rSign > secondSign2.rSign) && (secondSign2.rSign > r) ) {
			nextSign2.setPoint(firstSign2.rSign, firstSign2.lSign+1);
			if( getSymbol(nextSign2) == '=' )
				nextSign2.setPoint(firstSign2.rSign,firstSign2.lSign-1);
			turn1 = true;
		}
		if( !turn1 ) {
			if(firstSign2.lSign != secondSign2.lSign)
				nextSign2.setPoint(firstSign2.rSign-1,firstSign2.lSign);
			else
				nextSign2 = firstSign2 + (firstSign2-secondSign2); 
		}
	}
	else if( firstSign2.rSign < r ) {
		if( (firstSign2.rSign < secondSign2.rSign) && (secondSign2.rSign < r) ) {
			nextSign2.setPoint(firstSign2.rSign, firstSign2.lSign+1);
			if( getSymbol(nextSign2) == '=' )
				nextSign2.setPoint(firstSign2.rSign,firstSign2.lSign-1);
			turn2 = true;
		}
		if( !turn2 ) {
			if(firstSign2.lSign != secondSign2.lSign)
				nextSign2.setPoint(firstSign2.rSign+1,firstSign2.lSign); 
			else
				nextSign2 = firstSign2 + (firstSign2-secondSign2); 
		}
	}
	else {
		if( firstSign2.lSign > l ) {
			if(firstSign2.rSign != secondSign2.rSign)
				nextSign2.setPoint(firstSign2.rSign,firstSign2.lSign-1);
			else
				nextSign2 = firstSign2 + (firstSign2-secondSign2); 
		}
		else if( firstSign2.lSign < l ){
			if(firstSign2.rSign != secondSign2.rSign)
				nextSign2.setPoint(firstSign2.rSign,firstSign2.lSign+1);
			else
				nextSign2 = firstSign2 + (firstSign2-secondSign2); 
		}
		else
			nextSign2 = firstSign2 + (firstSign2-secondSign2); 
	}

	//如果没有碰到食物(且没有死亡的情况下)，删除蛇尾，压入新的蛇头
	if(getSymbol(nextSign2)!='*' && !isDead(nextSign2)) {    
		//删除蛇尾 
		lastSign2 = autoSnake.front(); 
		snakeMap[lastSign2.lSign][lastSign2.rSign] = ' '; 
		autoSnake.pop(); 
		//更新蛇头 
		secondSign2 = firstSign2; 
		//压入蛇头 
		autoSnake.push(nextSign2); 
		firstSign2 = autoSnake.back(); 
		snakeMap[firstSign2.lSign][firstSign2.rSign] = 'c'; 
		//没有吃食 
		eatFood = false; 
		isDead = true;
	}

	else if(getSymbol(nextSign2)=='*' && !isDead(nextSign2)) { 
		secondSign2 = firstSign2; 
		snakeMap[nextSign2.lSign][nextSign2.rSign] = 'c'; 
		//只压入蛇头 
		autoSnake.push(nextSign2); 
		firstSign2 = autoSnake.back(); 
		eatFood = true; 
		isDead = true;
		//加分 
		//score += 10; 
	}
	else
		isDead = false;
	return eatFood;
}

bool Csnake::UpdataGame() { 
	//初始化得分0 
	static int score = 0; 
	//获取用户按键信息 
	int choice; 
	choice = GetDirections(); 
	cout << " Total score: " << score << endl; 
	//随机产生食物所在坐标 
	int r,l; 
	//开始初始已经吃食，产生一个食物 
	static bool eatFood = true; 
	static bool eatFood2 = true;
	//如果吃了一个，才再出现第2个食物 
	if( eatFood || eatFood2 ) { 
		do { 
			//坐标范围限制在（1，1）到（line-2,row-2）对点矩型之间 
			srand(time(0));

			rr = r = (rand()%(row-2))+1; //横坐标 
			ll = l = (rand()%(line-2))+1;//竖坐标 
			//如果随机产生的坐标不是蛇身，则可行 
			//否则重新产生坐标 
			if(snakeMap[l][r] != 'X'|| snakeMap[l][r] != 'c') {	
				snakeMap[l][r] = '*';
			} 
		}while (snakeMap[l][r] == 'X' || snakeMap[l][r] == 'c'); 
	}
	eatFood2 = autoDecision(rr,ll);
	if( !isDead )
		return false;
	switch (choice) { 
		case 1://向上 
		//如果蛇头和蛇颈的横坐标不相同，执行下面操作 
		if(firstSign.rSign != secondSign.rSign)
			nextSign.setPoint(firstSign.rSign,firstSign.lSign-1); 
		//否则，如下在原本方向上继续移动 
		else 
			nextSign = firstSign + (firstSign-secondSign); 
		break; 
	
		case 2://向下 
		if(firstSign.rSign != secondSign.rSign)
			nextSign.setPoint(firstSign.rSign,firstSign.lSign+1); 
		else 
			nextSign = firstSign + (firstSign-secondSign); 
		break; 

		case 3://向左 
		if(firstSign.lSign != secondSign.lSign)
			nextSign.setPoint(firstSign.rSign-1,firstSign.lSign); 
		else 
			nextSign = firstSign + (firstSign-secondSign); 
		break; 

		case 4://向右 
		if(firstSign.lSign != secondSign.lSign)
			nextSign.setPoint(firstSign.rSign+1,firstSign.lSign); 
		else 
			nextSign = firstSign + (firstSign-secondSign); 
		break; 

		default: 
		nextSign = firstSign + (firstSign-secondSign); 
	}
	//如果没有碰到食物(且没有死亡的情况下)，删除蛇尾，压入新的蛇头
	if(getSymbol(nextSign)!='*' && !isDead(nextSign)) {    
		//删除蛇尾 
		lastSign = MySnake.front(); 
		snakeMap[lastSign.lSign][lastSign.rSign] = ' '; 
		MySnake.pop(); 
		//更新蛇头 
		secondSign = firstSign; 
		//压入蛇头 
		MySnake.push(nextSign); 
		firstSign = MySnake.back(); 
		snakeMap[firstSign.lSign][firstSign.rSign] = 'X'; 
		//没有吃食 
		eatFood = false; 
		return true; 
	}

	//-----吃食----- 
	else if(getSymbol(nextSign)=='*' && !isDead(nextSign)) { 
		secondSign = firstSign; 
		snakeMap[nextSign.lSign][nextSign.rSign] = 'X'; 
		//只压入蛇头 
		MySnake.push(nextSign); 
		firstSign = MySnake.back(); 
		eatFood = true; 
		//加分 
		score += 10; 
		return true; 
	}

	//-----死亡----- 
	else {
		cout << " Game Over! Your snake is Dead!" << endl;
		cout << " Your total score is " << score << endl; 
		return false;
	} 
} 

void Csnake::ShowGame() { 
	for(int i = 0; i < line; i++) { 
		for(int j = 0;j < row; j++) 
			cout << snakeMap[i][j]; 
		cout << endl; 
	}
	//挂起一段时间，单位是秒
	//Sleep(100); 
    //windows.h
	system("cls"); 
} 
