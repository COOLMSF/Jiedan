#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#define TRUE 1

int map[4][4];
int score = 0;
int game_check = 0;
int win_check = 0;

void make_map();
void rotate90();
void end_game() ;
void win_game();
void create_rand_num();
void move_left_with_merge();
void move_with_merge(char option) ;

void make_map()
{
	// 循环4次
	for (int i = 0; i < 4; i++) {
		printf("-------------------------\n");
		printf("|     |     |     |     |\n");
		printf("|%5d|%5d|%5d|%5d|\n",map[i][0],map[i][1],map[i][2],map[i][3]); printf("\n");
		printf("|     |     |     |     |\n");
		
	}
	printf("-------------------------\n");
	printf("score: %d\n", score);

}

void rotate90() 
{
	int temp[4][4];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i][j] = map[j][3 - i];
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			map[i][j] = temp[i][j];
		}
	}
}

void move_left_with_merge() 
{
	int temp_array[4][4] = { 0 };
	int new_array[4][4] = { 0 };
	int check= 0;
	
	for (int i = 0; i < 4; i++) {
		int loc = 0;
		for (int j = 0; j < 4; j++) {
			if (map[i][j] != 0) {
				temp_array[i][loc] = map[i][j];
				loc++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		int loc = 0;
		for (int j = 0; j < 4; j++) {
            // temp_array[i][j] + temp[i][j + 1]
            // 因为这里旋转了，所以只需要考虑数字向左移动
            // j < 3的时候移动，4的时候不移动
			if (j<3&&temp_array[i][j] == temp_array[i][j + 1]) {
                // 相加
				new_array[i][loc] = temp_array[i][j] + temp_array[i][j + 1];

                // 更新分数
				score += new_array[i][loc];

                // 更新计数器
				loc++;
				j++;
				
			}
            // 如果j=>3则直接复制，不用相加
			else {
				new_array[i][loc] = temp_array[i][j];
				loc++;
			}
		}
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
            // 2048地图与new_array比较
			if (map[i][j] != new_array[i][j]) {
                // 设置flag
				check = 1;
				
			}
			map[i][j] = new_array[i][j];
		}
	}
	if (check == 1) {
        // 创建随机数
		create_rand_num();

	}
	else {
        // check 不为1，说明2048地图与new_array
        // 里面的每个元素都相等，说明已经没有路走了
        // 结束游戏
		end_game();
	}
}

void move_with_merge(char option) 
{
	switch (option) {
    	// w为向上移动，旋转一次然后移动
		case 'w':
			rotate90();
			move_left_with_merge();
			rotate90();
			rotate90();
			rotate90();
			break;
 	   // a为向上移动，不需要旋转只需要移动
		case 'a':
			move_left_with_merge();
			break;
 	   // s为向下移动，旋转三次然后移动
		case 's':
			rotate90();
			rotate90();
			rotate90();
			move_left_with_merge();
			rotate90();
			break;
		case 'd':
 	   // d为向右移动，旋转二次然后移动
			rotate90();
			rotate90();
			move_left_with_merge();
			rotate90();
			rotate90();
			break;
	}
}

void create_rand_num() 
{
	int num = 0;
	int r,x,y;
	int random[2][16] = { 0 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j] == 0) {
				random[0][num] = i;
				random[1][num] = j;
				num++;
			}
		}
	}

	if (num > 0) {
		r = rand() % num;
		x = random[0][r];
		y = random[1][r];
		map[x][y] = (rand() % 2+1)*2;
		 
	}
}

void create_num_2() 
{
	int num = 0;
	int r, x, y;
	int random[2][16] = { 0 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j] == 0) {
				random[0][num] = i;
				random[1][num] = j;
				num++;
			}
		}
	}

	if (num > 0) {
		r = rand() % num;
		x = random[0][r];
		y = random[1][r];
		map[x][y] = 2;

	}

}

void end_game() 
{
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j] != 0) {
				game_check = 0;
				return;
			}
		}
	}
	game_check=1;
	
}

void win_game()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j] >= 2048) {
				win_check = 1;
				return;
			}
			
		
		}
	}
	
}

void make_map() 
{
	create_rand_num();
	create_rand_num();
	for (int i = 0; i < 4; i++) {

		printf("-------------------------\n");
		printf("|     |     |     |     |\n");
		printf("|%5d|%5d|%5d|%5d|\n", map[i][0], map[i][1], map[i][2], map[i][3]); printf("\n");
		printf("|     |     |     |     |\n");

	}
	printf("-------------------------\n");
	printf("score: %d\n", score);
}



int main() 
{
	printf("欢迎使用2048!\n");
	printf("按任意键继续\n"); getch();
	system("cls");
    // 初始化界面
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			map[i][j] = 0;
	}

    // 生成地图
	make_map();
	char option;

    // 无限循环 等待用户输入
	while (TRUE) {
		// 非缓冲输入
		option = _getch();
		move_with_merge(option);
		//system("cls");
		make_map();
		if (game_check == 1) {
			system("cls");
			printf("Game Over\n");
			printf("Score: %d \n ", score);
			return 0;
		}
		win_game();
		if (win_check == 1) {
			printf("Game Win\n");
			printf("Score: %d \n ", score);
		}


	}
 }
