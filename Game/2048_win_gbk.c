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
	// ѭ��4��
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
            // ��Ϊ������ת�ˣ�����ֻ��Ҫ�������������ƶ�
            // j < 3��ʱ���ƶ���4��ʱ���ƶ�
			if (j<3&&temp_array[i][j] == temp_array[i][j + 1]) {
                // ���
				new_array[i][loc] = temp_array[i][j] + temp_array[i][j + 1];

                // ���·���
				score += new_array[i][loc];

                // ���¼�����
				loc++;
				j++;
				
			}
            // ���j=>3��ֱ�Ӹ��ƣ��������
			else {
				new_array[i][loc] = temp_array[i][j];
				loc++;
			}
		}
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
            // 2048��ͼ��new_array�Ƚ�
			if (map[i][j] != new_array[i][j]) {
                // ����flag
				check = 1;
				
			}
			map[i][j] = new_array[i][j];
		}
	}
	if (check == 1) {
        // ���������
		create_rand_num();

	}
	else {
        // check ��Ϊ1��˵��2048��ͼ��new_array
        // �����ÿ��Ԫ�ض���ȣ�˵���Ѿ�û��·����
        // ������Ϸ
		end_game();
	}
}

void move_with_merge(char option) 
{
	switch (option) {
    	// wΪ�����ƶ�����תһ��Ȼ���ƶ�
		case 'w':
			rotate90();
			move_left_with_merge();
			rotate90();
			rotate90();
			rotate90();
			break;
 	   // aΪ�����ƶ�������Ҫ��תֻ��Ҫ�ƶ�
		case 'a':
			move_left_with_merge();
			break;
 	   // sΪ�����ƶ�����ת����Ȼ���ƶ�
		case 's':
			rotate90();
			rotate90();
			rotate90();
			move_left_with_merge();
			rotate90();
			break;
		case 'd':
 	   // dΪ�����ƶ�����ת����Ȼ���ƶ�
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
	printf("��ӭʹ��2048!\n");
	printf("�����������\n"); getch();
	system("cls");
    // ��ʼ������
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			map[i][j] = 0;
	}

    // ���ɵ�ͼ
	make_map();
	char option;

    // ����ѭ�� �ȴ��û�����
	while (TRUE) {
		// �ǻ�������
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
