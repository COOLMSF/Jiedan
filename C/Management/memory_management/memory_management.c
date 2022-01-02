#include "memory_management.h"

// ģ�� �ڴ�� 
typedef struct{
unsigned char is_available;         /* block�Ƿ����ʹ�� */
unsigned int prior_blocksize;       /* ǰһ������Ĵ�С */
unsigned int current_blocksize;     /*�����С */
}mem_control_block;

//��Ҫ˵������ʼ��malloc��gloabl varialbe��heap�ڴ��ͷ����
void malloc_init(void)
{
    mem_control_block * mcb = NULL;

    /* ȷ�϶ѵ���ʼ��ַ */
	int managed_memory_start = (unsigned int)malloc_addr;
    int managed_memory_size;
    /* ȷ�϶ѵĴ�С */
    managed_memory_size = malloc_size;
    /*ȷ�϶ѵĽ�����ַ */
    managed_memory_end = managed_memory_start + managed_memory_size;

    /* ʹMCBָ��ѵ���ʼ��ַ */
    mcb = (mem_control_block *)managed_memory_start;
    /*��һ��block�ǿ���ʹ�õ� */
    mcb->is_available = 1;
    /*��һ������֮ǰû������ */
    mcb->prior_blocksize = 0;
    /*��һ����Ĵ�С�ǶѵĴ�С�Ϳ��ƿ�Ĵ�С֮�� */
    mcb->current_blocksize = managed_memory_size - sizeof(mem_control_block);
    /* ��ʼ����� */
    has_initialized = 1;
}

// ʵ�� malloc ���� 
void * malloc(unsigned int numbytes)
{
    unsigned int current_location,otherbck_location;
    /* ����current_location��ͬ������Ͷ��һ��memory_control_block */
    mem_control_block * current_location_mcb = NULL,* other_location_mcb = NULL;
    /* varialbe���ڱ��淵��ֵ����������Ϊ0��ֱ�������ҵ����ʵĶ����� */
    void * memory_location = NULL;
    /* Ŀǰ�ķֿ�ߴ� */
    unsigned int process_blocksize;

    /* �����δ��ʼ�����ʼ�� */
    if(! has_initialized) 
	{
        malloc_init();
    }

    /* �ӱ��������ڴ����㿪ʼ���� */
    current_location = managed_memory_start;
    /* ��������ֱ�����������з���Ŀռ䡣 */
    while(current_location != managed_memory_end)
	{
         /* current_location �� current_location_mcb ָ��ͬһ����ַ�� Ȼ����
         * current_location_mcb����������ȷ�ģ����Կ��԰�����Ϊһ���ṹ��ʹ�á�
         * ��һ����Чָ�룬�������ǿ��������������ַ��
         */
        current_location_mcb = (mem_control_block *)current_location;
        /* �жϵ�ǰ�����Ƿ����ʹ�� */
        if(current_location_mcb->is_available){
            /* �жϵ�ǰ��Ĵ�С�Ƿ���ȫ�ʺ���Ҫ  */
            if((current_location_mcb->current_blocksize == numbytes))
			{
                /*  ���Ѳ��ٿ��� */
                current_location_mcb->is_available = 0;
                /* ��ȡ�ڴ��ַ */
                memory_location = (void *)(current_location + sizeof(mem_control_block));
                /* �˳�ѭ�� */
                break;
            /* �жϵ�ǰ�����С�Ƿ����Ի���һ���µ����� */
            }else if(current_location_mcb->current_blocksize >= numbytes + sizeof(mem_control_block)){
                /* �Ѳ��ٿ��� */
                current_location_mcb->is_available = 0;
                /* ��ΪҪ�Ե�ǰ����зָ�ڸı䵱ǰ��Ĵ�С֮ǰ������Ӧ��
                 *������ֵĴ�С��
                 */
                process_blocksize = current_location_mcb->current_blocksize;
                /* ���ڿ��Ըı�blcok�Ĵ�С */
                current_location_mcb->current_blocksize = numbytes;

                /* �ҵ�memory_control_block��ʣ����ͷ���������ò�����û�еĿ顣
                 *�������ܱ�������
                 */
                other_location_mcb = (mem_control_block *)(current_location + numbytes \
                                                + sizeof(mem_control_block));
                /* ʣ���������Ȼ����ʹ�� */
                other_location_mcb->is_available = 1;
                /*��Ȼ����֮ǰ�Ŀ��С��numbytes */
                other_location_mcb->prior_blocksize = numbytes;
                /* ���ĳߴ�Ӧ�ñ�С */
                other_location_mcb->current_blocksize = process_blocksize - numbytes \
                                                - sizeof(mem_control_block);

                /* �ҵ�memory_control_block�ڵ�ǰblock֮���block��ͷ���������ò���--prior_blocksize��
                 *���ò���--prior_blocksize��
                 */
                otherbck_location = current_location + process_blocksize \
                                            + sizeof(mem_control_block);
                /* ��Ҫ�����������Ƿ��ڹ����ڴ�ı�Ե�� */
                if(otherbck_location != managed_memory_end)
				{
                    other_location_mcb = (mem_control_block *)(otherbck_location);
                    /*����ǰ�������С�Ѿ��ı��ˣ�*/
                    other_location_mcb->prior_blocksize = process_blocksize\
                        - numbytes - sizeof(mem_control_block);
                }
                /*ӵ�б�ռ�õ����飬������ʣ������� */
                memory_location = (void *)(current_location + sizeof(mem_control_block));
                /* �뿪ѭ�� */
                break;
            }
        }
        /* ��ǰ���鲻���û������С̫С��ת����һ������*/��
        current_location += current_location_mcb->current_blocksize \
                                    + sizeof(mem_control_block);
    }
    /* �����Ȼû��һ����Ч��λ�ã������ò�����NULL */
    if(memory_location == NULL)    
	{
        return NULL;
    }
    /* ����ָ�� */
    return memory_location;
}

// ʵ�� free ���� 
void free(void *firstbyte)
{
    unsigned int current_location,otherbck_location;
    mem_control_block * current_mcb = NULL,* next_mcb = NULL,* prior_mcb \
                                = NULL,* other_mcb = NULL;
    /* �Ӹ�����ָ����б��ݣ��ҵ���ǰ�� */
    current_location = (unsigned int)firstbyte - sizeof(mem_control_block);
    current_mcb = (mem_control_block *)current_location;
    /* ����������Ϊ�ɻ�õ� */
    current_mcb->is_available = 1;

    /* �ҵ���һ�������λ�� */
    otherbck_location = current_location + sizeof(mem_control_block) \
                                    + current_mcb->current_blocksize;
    /* ��Ҫ�����������Ƿ��ڹ����ڴ�ı�Ե�� */
    if(otherbck_location != managed_memory_end)
	{
        /* ָ����һ������ */
        next_mcb = (mem_control_block *)otherbck_location;
        /* ��Ҫ���������һ�������Ƿ����ʹ�� */
        if(next_mcb->is_available){
            /* ��Ϊ������һ������Ҳ�ǿɻ�õģ�Ӧ�úϲ����� */
            current_mcb->current_blocksize = current_mcb->current_blocksize \
                + sizeof(mem_control_block) + next_mcb->current_blocksize;

            /* �ϲ����������飬������Ҫ�ı���������� prior_blocksize��
             *��������֮������飬ֻҪ�ҵ���һ�������λ�á�
             */
            otherbck_location = current_location + sizeof(mem_control_block) \
                                    + current_mcb->current_blocksize;
            /* ��Ҫ�����������Ƿ��ڹ����ڴ�ı�Ե�� */
            if(otherbck_location != managed_memory_end)
			{
                other_mcb = (mem_control_block *)otherbck_location;
                /*����ǰ�������С�Ѿ��ı��ˣ�*/
                other_mcb->prior_blocksize = current_mcb->current_blocksize;
            }
        }
    }

    /* ��Ҫ�����������Ƿ��ڹ����ڴ�ı�Ե�� */
    if(current_location != managed_memory_start)
	{
        /* ָ����ǰ������ */
        prior_mcb = (mem_control_block *)(current_location - sizeof(mem_control_block)\
                                            - current_mcb->prior_blocksize);
        /* ��Ҫ�������ǰһ�������Ƿ����ʹ�� */
        if(prior_mcb->is_available)
		{
            /* ��Ϊ��֮ǰ������Ҳ�ǿɻ�õģ�����Ӧ�úϲ����� */
            prior_mcb->current_blocksize = prior_mcb->current_blocksize \
                + sizeof(mem_control_block) + current_mcb->current_blocksize;

            /* ���Ǻϲ����������飬����������Ҫ�ı���������� prior_blocksize��
             *��������֮������飬ֻҪ�ҵ���һ�������λ�á�
             */
            otherbck_location = current_location + sizeof(mem_control_block) \
                                    + current_mcb->current_blocksize;
            /* ��Ҫ�����������Ƿ��ڹ����ڴ�ı�Ե�� */
            if(otherbck_location != managed_memory_end)
			{
                other_mcb = (mem_control_block *)otherbck_location;
                /*����ǰ�������С�Ѿ��ı��ˣ�**����ǰ�������С�Ѿ��ı��� */
                other_mcb->prior_blocksize = prior_mcb->current_blocksize;
            }
        }
    }
}

int main(int argc, char const* argv[])
{
    int *p;

    p = (int *)malloc(sizeof(int));
    *p = 0x11;

    printf("%d", *p);
}
