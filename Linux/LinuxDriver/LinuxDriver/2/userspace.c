#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>

#define DEVICE "/dev/charDev"

int debug = 1, fd = 0;
// Test
int ppos = 0;

int write_device()
{
        int write_length = 0;
        ssize_t ret;
        char *data = (char *)malloc(1024 * sizeof(char));

        printf("please enter the data to write into device\n");
        scanf(" %[^\n]", data); /* a space added after so that it reads white space,
                                 %[^\n] is   addeed so that it takes input until new line*/
        write_length = strlen(data);
        if (debug)
                printf("the length of dat written = %d\n", write_length);
        ret = write(fd, data, write_length);
        // ret = write(fd, data, write_length, &ppos);
        if (ret == -1)
                printf("writting failed\n");
        else
                printf("writting success\n");
        if (debug)fflush(stdout); /*not to miss any log*/
        free(data);
        return 0;
}

int read_device()
{
        int read_length = 0;
        ssize_t ret;
        char *data = (char *)malloc(1024 * sizeof(char));

        printf("enter the length of the buffer to read\n");
        scanf("%d", &read_length);

        if (debug)
                printf("the read length selected is %d\n", read_length, &ppos);
        memset(data, 0, sizeof(data));
        data[0] = '\0';
        ret = read(fd, data, read_length);
        // ret = read(fd, data, read_length, &ppos);
        printf("DEVICE_READ : %s\n", data);
        if (ret == -1)
                printf("reading failed\n");
        else
                printf("reading success\n");
        if (debug)
                fflush(stdout);/*not to miss any log*/
        free(data);
        return 0;
}

int lseek_device()
{
        int lseek_offset = 0, seek_value = 0;
        int counter = 0; /* to check if function called multiple times or loop*/
        counter++;
        printf("counter value = %d\n", counter);
        printf("enter the seek offset\n");
        scanf("%d", &lseek_offset);
        if (debug)
                printf("seek_offset selected is %d\n", lseek_offset);
        printf("1 for SEEK_SET, 2 for SEEK_CUR and 3 for SEEK_END\n");
        scanf("%d", &seek_value);
        printf("seek value = %d\n", seek_value);

        switch (seek_value) {
        case 1: lseek(fd, lseek_offset, SEEK_SET);
                return 0;
                break;
        case 2: lseek(fd, lseek_offset, SEEK_CUR);
                return 0;
                break;
        case 3: lseek(fd, lseek_offset, SEEK_END);
                return 0;
                break;
        default :
                printf("unknown  option selected, please enter right one\n");
                break;
        }
        if (debug)
                fflush(stdout);/*not to miss any log*/
        return 0;
}

int lseek_write()
{
        lseek_device();
        write_device();
        return 0;
}

int lseek_read()
{
        lseek_device();
        read_device();
        return 0;
}

int main()
{
        int value = 0;
        if (access(DEVICE, F_OK) == -1) {
                printf("module %s not loaded\n", DEVICE);
                return 0;
        } else
                printf("module %s loaded, will be used\n", DEVICE);

        while (1) {
                printf("please enter:\n\
                    \t 1 to write\n\
                    \t 2 to read\n\
                    \t 3 to lseek and write\n\
                    \t 4 to lseek and read\n");
                scanf("%d", &value);
                switch (value) {
                case 1 : printf("write option selected\n");
                        fd = open(DEVICE, O_RDWR);
                        write_device();
                        close(fd); /*closing the device*/
                        break;
                case 2 : printf("read option selected\n");
                        /* dont know why but i am suppoesed to open it for
                        writing and close it, i cant keep  open and read.
                        its not working, need to sort out why is that so */
                        fd = open(DEVICE, O_RDWR);
                        read_device();
                        close(fd); /*closing the device*/
                        break;
                case 3 : printf("lseek  option selected\n");
                        fd = open(DEVICE, O_RDWR);
                        lseek_write();
                        close(fd); /*closing the device*/
                        break;
                case 4 : printf("lseek  option selected\n");
                        fd = open(DEVICE, O_RDWR);
                        lseek_read();
                        close(fd); /*closing the device*/
                        break;
                default : printf("unknown  option selected, please enter right one\n");
                        break;
                }
        }
        return 0;
}
