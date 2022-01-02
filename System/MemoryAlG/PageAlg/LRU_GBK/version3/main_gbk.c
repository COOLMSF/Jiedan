#include<stdio.h>
 
int min_time_pos(int time[], int n)
{
    int i, minimum = time[0], pos = 0;
    for(i = 1; i < n; ++i)
    {
        if(!(time[i] > minimum))
        {
            pos = i;
            minimum = time[i];
        }
    }
    return pos;
}
 
int main(int argc, char *argv[])
{
    int FrameNumber = 0, PageNumber = 0;
    int counter = 0, flag1 = 0, flag2 = 0;
    int  i = 0, j = 0, pos = 0, faults = 0;
    int frames[10] = { 0 }, pages[30] = { 0 }, time[10] = { 0 };
    puts("输入帧数量: ");
    scanf("%d", &FrameNumber);
    puts("输入页数量: ");
    scanf("%d", &PageNumber);
    puts("输入页: ");
    for(i = 0; i < PageNumber; ++i){
        scanf("%d", &pages[i]);
    }
    // 初始化
    for(i = 0; i < FrameNumber; ++i)
    {
        frames[i] = -1;
    }
    
    for(i = 0; i < PageNumber; ++i)
    {
        flag1 = flag2 = 0;
        // 命中页
        for(j = 0; j < FrameNumber; ++j){
            if(frames[j] == pages[i]){
                counter++;
                time[j] = counter;
                   flag1 = flag2 = 1;
                   break;
               }
        }
        if(flag1 == 0)
        {
            for(j = 0; j < FrameNumber; ++j)
            {
                if(frames[j] == -1)
                {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }    
        }
        if(flag2 == 0)
        {
            pos = min_time_pos(time, FrameNumber);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }
        puts("");
        for(j = 0; j < FrameNumber; ++j)
        {
            printf("%d\t", frames[j]);
        }
    }
    printf("\n\n缺页数量 = %d", faults);
    return 0;
}
