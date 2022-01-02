#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>           /* this is the file structure, file open read close */
#include <linux/cdev.h>         /* this is for character device, makes cdev avilable*/
#include <linux/semaphore.h>    /* this is for the semaphore*/
#include <linux/uaccess.h>      /* this is for copy_user vice vers*/

int chardev_init(void);
void chardev_exit(void);

/*new code*/
#define BUFFER_SIZE 1024
static char device_buffer[BUFFER_SIZE];
struct semaphore sem;
struct cdev *mcdev;     /* this is the name of my char driver that i will be registering*/
int major_number;       /* will store the major number extracted by dev_t*/
int ret;                /* used to return values*/
dev_t dev_num;          /* will hold the major number that the kernel gives*/

#define DEVICENAME "charDev"

int chardev_init(void)
{
        /* we will get the major number dynamically this is recommended please read ldd3*/
        ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICENAME);
        if (ret < 0) {
                printk(KERN_ALERT " charDev : failed to allocate major number\n");
                return ret;
        } else
                printk(KERN_INFO " charDev : mjor number allocated succesful\n");
        major_number = MAJOR(dev_num);
        printk(KERN_INFO "charDev : major number of our device is %d\n", major_number);
        printk(KERN_INFO "charDev : to use mknod /dev/%s c %d 0\n", DEVICENAME, major_number);

        mcdev = cdev_alloc(); /* create, allocate and initialize our cdev structure*/
        mcdev->owner = THIS_MODULE;

        /* we have created and initialized our cdev structure now we need to
        add it to the kernel*/
        ret = cdev_add(mcdev, dev_num, 1);
        if (ret < 0) {
                printk(KERN_ALERT "charDev : device adding to the kerknel failed\n");
                return ret;
        } else
                printk(KERN_INFO "charDev : device additin to the kernel succesful\n");
        sema_init(&sem, 1); /* initial value to one*/

        return 0;
}

void chardev_exit(void)
{
        cdev_del(mcdev); /*removing the structure that we added previously*/
        printk(KERN_INFO " CharDev : removed the mcdev from kernel\n");

        unregister_chrdev_region(dev_num, 1);
        printk(KERN_INFO  " CharDev : unregistered the device numbers\n");
        printk(KERN_ALERT " charDev : character driver is exiting\n");
}

module_init(chardev_init);
module_exit(chardev_exit);
