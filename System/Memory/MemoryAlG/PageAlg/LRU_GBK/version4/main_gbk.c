#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    
    int length;
    int num_frames;

    printf("�������ݴ�С: ");
    scanf("%d", &length);

    char ref_string[length*2];

    char hold;
    printf("��������: ");
    // scanf("%[^\n]%*c", ref_string);

    int reference_str[length];

    for (int i = 0; i < length; i++)
    {
        scanf("%d ", &reference_str[i]);
    }
    scanf("%c", &hold);
    scanf("%c", &hold);

    printf("����֡��С: ");
    scanf("%d", &num_frames);
    
    int memory[num_frames];
    for (int i = 0; i < num_frames; i++)
    {
        memory[i] = -1;
    }
    
    // LRU�㷨
    int fault_count = 0;

    for (int i = 0; i < length; i++)
    {
        // �������ҳ
        int cur_page = reference_str[i];
        int page_found = 0;

        // �����Ƿ�����
        for(int j = 0; j < num_frames; j++)
        {
            if(memory[j] == cur_page)
            {
                page_found = 1;
                break;
            }
        }


        // ҳû�ҵ�
        if(!page_found)
        {
            fault_count++;
            int is_cached = 0;
            for(int j = 0; j < num_frames; j++)
            {
                if(memory[j] == -1)
                {
                    memory[j] = cur_page;
                    break;
                }
            }

            if(!is_cached)
            {
                int check_count = 0;
                int check_status[num_frames];
                for(int m = 0; m < num_frames; m++)
                {
                    check_status[m] = 0;
                }

                for(int cur = i-1; cur >= 0; cur--)
                {
                    int val = reference_str[cur];

                    for(int n= 0; n < num_frames; n++)
                    {
                        if(val == memory[n])
                        {
                            check_status[n] = 1;
                            check_count++;
                            break;
                        }
                    }

                    if(check_count == num_frames-1)
                        break;
                }
                for(int cur = 0; cur < num_frames; cur++)
                {
                    if(check_status[cur] == 0)
                    {
                        memory[cur] = cur_page;
                        break;
                    }
                }
            }

            for(int j = 0; j < num_frames; j++)
            {
                printf("%d\t", memory[j]);
            }
            printf("\tPage Fault Num : %d\n", fault_count);

        }
        else
        {
            for(int j = 0; j < num_frames; j++)
            {
                printf("%d\t", memory[j]);
            }
            printf("\n");
            
        }

    }
    printf("\n ȱҳ����: %d\n", fault_count);

    return 0;
}