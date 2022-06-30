#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


bool search(int key, vector<int>& fr)
{
      // 遍历找到key
	for (int i = 0; i < fr.size(); i++)
		if (fr[i] == key)
			return true;
	return false;
}

int predict(int pg[], vector<int>& fr, int pn, int index)
{
      // 设置最远访问为index
	int res = -1, farthest = index;
	for (int i = 0; i < fr.size(); i++) {
		int j;
		for (j = index; j < pn; j++) {
			if (fr[i] == pg[j]) {
                        // 更新最远信息
				if (j > farthest) {
					farthest = j;
					res = i;
				}
				break;
			}
		}

		if (j == pn)
			return i;
	}

	return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{

      // 容器
	vector<int> fr;

	int hit = 0;
	for (int i = 0; i < pn; i++) {

            // pg里面搜索fr
		if (search(pg[i], fr)) {
                  // 命中
			hit++;
			continue;
		}
            // 数量小于fn
		if (fr.size() < fn)
			fr.push_back(pg[i]);
		else {
                  // 预测
			int j = predict(pg, fr, pn, i + 1);
			fr[j] = pg[i];
		}
	}
	printf("No. of hits = %d\n",hit);
	printf("No. of misses = %d\n", pn - hit);
}

int opt()
{
      int pg[400];

      // 生成随机数种子
      srand((int)time(0) * 1000);
      // 填充
      for (int i = 0; i < 400; i++) {
   	   	pg[i] = rand() % 10;
      }
   	int pn = sizeof(pg) / sizeof(pg[0]);
   	int fn = 10;
       // 调用opt算法
   	optimalPage(pg, pn, fn);
   	return 0;
}

int fifo()
{
    
      int referenceString[400];
      int pageFaults = 0, m, n, s, pages, frames;

      pages = 40;

      // 生成种子
    	srand((int)time(0) * 1000);
      for(m = 0; m < pages; m++) {
            // 赋值指令
	    referenceString[m] = rand() % 10;
      }
      frames = 10;
      int temp[frames];
      // 初始化
      for(m = 0; m < frames; m++)
      {
            temp[m] = -1;
      }
      // 遍历所有页
      for(m = 0; m < pages; m++)
      {
            s = 0;
            // 遍历所有帧
            for(n = 0; n < frames; n++)
            {
                  // 命中
                  if(referenceString[m] == temp[n])
                  {
                        s++;
                        pageFaults--;
                  }
            }     
            pageFaults++;
            // 更新
            if((pageFaults <= frames) && (s == 0))
            {
                  temp[m] = referenceString[m];
            }   
            else if(s == 0)
            {
                  temp[(pageFaults - 1) % frames] = referenceString[m];
            }
            printf("\n");
            for(n = 0; n < frames; n++)
            {     
                  printf("%d\t", temp[n]);
            }
      } 
      printf("\nTotal Page Faults:\t%d\n", pageFaults);
      return 0;
}
int min_time_pos(int time[], int n)
{
      int i, minimum = time[0], pos = 0;
 
      // 找到时间最小的页面
      for(i = 1; i < n; ++i){
            if(time[i] < minimum){
                  minimum = time[i];
                  pos = i;
            }
      }

return pos;
}
 
int lru()
{
      int no_of_frames, no_of_pages, frames[10], pages[40], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;
      // 初始化
   	no_of_frames = 10;
      no_of_pages = 40;
      // srand(time(0) * 1000);

      // 填充指令
      for(i = 0; i < no_of_pages; ++i){
       // scanf("%d", &pages[i]);
       pages[i] = rand() % 10;
      }
    
      // 初始化
      for(i = 0; i < no_of_frames; ++i){
       frames[i] = -1;
      }
    
      for(i = 0; i < no_of_pages; ++i){
            flag1 = flag2 = 0;
    
            for(j = 0; j < no_of_frames; ++j){
                // 命中
               if(frames[j] == pages[i]){
               counter++;
               // 设置计数器
               time[j] = counter;
               // 设置flalg
               flag1 = flag2 = 1;
               break;
            }
      }
    
      // 检查flag
       if(flag1 == 0){
          for(j = 0; j < no_of_frames; ++j){
              if(frames[j] == -1){
              counter++;
              faults++;
              frames[j] = pages[i];
              time[j] = counter;
              flag2 = 1;
              break;
       }
       }
       }
    
       if(flag2 == 0){
          pos = min_time_pos(time, no_of_frames);
          counter++;
          faults++;
          frames[pos] = pages[i];
          time[pos] = counter;
       }
    
       printf("\n");
    
       for(j = 0; j < no_of_frames; ++j){
       printf("%d\t", frames[j]);
       }
}
printf("\n\nTotal Page Faults = %d", faults);
    
    return 0;
}

int welcome()
{
	puts("1:) FIFO");
	puts("2:) OPT");
	puts("3:) LUR");
}

int main()
{
	int input;

      // 输出选择信息
	welcome();
	puts("Input your choice:");

      // 获取输入
	scanf("%d", &input);

      // 调用相关算法
	switch (input) {
		case 1:
			fifo();
			break;
		case 2:
			opt();
			break;
		case 3:
			lru();
			break;
	}
}
