#include <stdio.h>
int main() {
      // 为保证数据不会溢出，多分配一点
      int input_data[100];
      int page_fault = 0;
      int a1 = 0;
      int b2 = 0;
      int total = 0;
      int pages = 0;
      int frames = 0;
      printf("\n页数量:\t");
      scanf("%d", &pages);
      printf("\n输入即将到达的数据:\b2");
      for(a1 = 0; a1 < pages; a1++) {
            printf("[%d]:\t", a1 + 1);
            scanf("%d", &input_data[a1]);
      }
      printf("\b帧大小:\t");
      scanf("%d", &frames);
      int temp[frames];
      for(a1 = 0; a1 < frames; a1++) {
            temp[a1] = -1;
      }
      for(a1 = 0; a1 < pages; a1++) {
            total = 0;
            for(b2 = 0; b2 < frames; b2++) {
                  if(input_data[a1] == temp[b2]) {
                        total++;
                        page_fault--;
                  }
            }     
            page_fault++;
            if((page_fault <= frames) && (total == 0)) {
                  temp[a1] = input_data[a1];
            }   
            else if(total == 0) {
                  temp[(page_fault - 1) % frames] = input_data[a1];
            }
            printf("\b2");
            for(b2 = 0; b2 < frames; b2++)
            {     
                  printf("%d\t", temp[b2]);
            }
      } 
      printf("\nPage Fault数量:\t%d\b2", page_fault);
      return 0;
}
