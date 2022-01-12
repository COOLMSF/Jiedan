/* Disk on RAM Driver */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <uapi/linux/hdreg.h> 

#define RB_FIRST_MINOR 0
#define RB_MINOR_CNT 16
 
static u_int rb_major = 0;
static u8 *dev_data;

#define RAM_DISK_SIZE	(50 * 1024 * 1024)
#define RB_DEVICE_SIZE 1024
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))
 
#define SECTOR_SIZE 512
#define MBR_SIZE SECTOR_SIZE
#define MBR_DISK_SIGNATURE_OFFSET 440
#define MBR_DISK_SIGNATURE_SIZE 4
#define PARTITION_TABLE_OFFSET 446
#define PARTITION_ENTRY_SIZE 16 
#define PARTITION_TABLE_SIZE 64 
#define MBR_SIGNATURE_OFFSET 510
#define MBR_SIGNATURE_SIZE 2
#define MBR_SIGNATURE 0xAA55
#define BR_SIZE SECTOR_SIZE
#define BR_SIGNATURE_OFFSET 510
#define BR_SIGNATURE_SIZE 2
#define BR_SIGNATURE 0xAA55     

 /*
 * The internal structure representation of our Device
 */
static struct rb_device
{
    /* Size is the size of the device (in sectors) */
    unsigned int size;
    /* For exclusive access to our request queue */
    spinlock_t lock;
    /* Our request queue */
    struct request_queue *rb_queue;
    /* This is kernel's representation of an individual disk device */
    struct gendisk *rb_disk;
} rb_dev;


typedef struct
{
    unsigned char boot_type; 
    unsigned char start_head;
    unsigned char start_sec:6;
    unsigned char start_cyl_hi:2;
    unsigned char start_cyl;
    unsigned char part_type;
    unsigned char end_head;
    unsigned char end_sec:6;
    unsigned char end_cyl_hi:2;
    unsigned char end_cyl;
    unsigned int abs_start_sec; 
    unsigned int sec_in_part;
} PartEntry;
 
typedef PartEntry PartTable[4];
 
static PartTable def_part_table =
{
    {
        boot_type: 0x00,
        start_head: 0x0,
        start_sec: 0x1,
        start_cyl: 0x00,
        part_type: 0x83,   
        end_head: 0x0,
        end_sec: 0x1,
        end_cyl: 0x50,
        abs_start_sec: 0x00000001,
        sec_in_part: 0x00005000
    },
    {
        boot_type: 0x00,
        start_head: 0x00,
        start_sec: 0x2,
        start_cyl: 0x50,
        part_type: 0x83,    
        end_head: 0x0,
        end_sec: 0x3,
        end_cyl_hi:0x1,
        end_cyl: 0x90,
        abs_start_sec: 0x00005001,
        sec_in_part: 0x0000C800
    },
    { 
        boot_type: 0x00,
        start_head: 0x00,
        start_sec: 0x4,
        start_cyl: 0x90,
        part_type: 0x83,    
        end_head: 0x0,
        end_sec: 0x5,
        end_cyl_hi:0x2,
        end_cyl: 0x90,
        abs_start_sec: 0x00011801,
        sec_in_part: 0x00007800
    },
    {}
};


 
static int rb_open(struct block_device *bdev, fmode_t mode)
{
    unsigned unit = iminor(bdev->bd_inode);
 
    printk(KERN_INFO "rb: Device is opened\n");
    printk(KERN_INFO "rb: Inode number is %d\n", unit);
 
    if (unit > RB_MINOR_CNT)
        return -ENODEV;
    return 0;
}
 
static void rb_close(struct gendisk *disk, fmode_t mode)
{
    printk(KERN_INFO "rb: Device is closed\n");
}

#define RAM_DISK_SIZE	(50 * 1024 * 1024)
#define RB_DEVICE_SIZE 1024
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))
 
#define SECTOR_SIZE 512
#define MBR_SIZE SECTOR_SIZE
#define MBR_DISK_SIGNATURE_OFFSET 440
#define MBR_DISK_SIGNATURE_SIZE 4
#define PARTITION_TABLE_OFFSET 446
#define PARTITION_ENTRY_SIZE 16 
#define PARTITION_TABLE_SIZE 64 
#define MBR_SIGNATURE_OFFSET 510
#define MBR_SIGNATURE_SIZE 2
#define MBR_SIGNATURE 0xAA55
#define BR_SIZE SECTOR_SIZE
#define BR_SIGNATURE_OFFSET 510
#define BR_SIGNATURE_SIZE 2
#define BR_SIGNATURE 0xAA55  

int ram_disk_device_init(void)
{
    u8 * disk_add;
    dev_data = vmalloc(RAM_DISK_SIZE);
    if (dev_data == NULL)
        return -ENOMEM;
    

    //Main partition table
    memset(dev_data, 0x0, 512);
    *(unsigned long *)(dev_data + 440) = 0x78D2314D;//ID
    memcpy(dev_data + 446, &def_part_table, 64); //offset 446 write part table, all count: 64 
    *(unsigned short *)(dev_data + 510) = 0xAA55; //offset 510 write, disk signature


    return RAM_DISK_SIZE / SECTOR_SIZE;
}

// release vmalloc 
void ram_disk_divce_free(void)
{
    vfree(dev_data);
}
 

void ram_disk_device_write(sector_t sector_off, u8 *buffer, unsigned int sectors)
{
    memcpy(dev_data + sector_off * SECTOR_SIZE, buffer, sectors * SECTOR_SIZE);
}

void ram_disk_device_read(sector_t sector_off, u8 *buffer, unsigned int sectors)
{
    memcpy(buffer, dev_data + sector_off * SECTOR_SIZE, sectors * SECTOR_SIZE);
}


static int rb_transfer(struct request *req)
{
    int dir = rq_data_dir(req);
    sector_t start_sector = blk_rq_pos(req);
    unsigned int sector_cnt = blk_rq_sectors(req);
 
    struct bio_vec bv;
    struct req_iterator iter;
 
    sector_t sector_offset;
    unsigned int sectors;
    u8 *buffer;
 
    int ret = 0;
 
    sector_offset = 0;
    rq_for_each_segment(bv, req, iter)
    {
        buffer = page_address(bv.bv_page) + bv.bv_offset;
        if (bv.bv_len % SECTOR_SIZE != 0)
        {
            printk(KERN_ERR "rb: Should never happen: "
                "bio size (%d) is not a multiple of SECTOR_SIZE (%d).\n"
                "This may lead to data truncation.\n",
                bv.bv_len, SECTOR_SIZE);
            ret = -EIO;
        }
        sectors = bv.bv_len / SECTOR_SIZE;
        printk(KERN_DEBUG "rb: Sector Offset: %lld; Buffer: %p; Length: %d sectors\n",
            sector_offset, buffer, sectors);
        if (dir == WRITE) 
        {
            /* Write to the device */
            ram_disk_device_write(start_sector + sector_offset, buffer, sectors);
        }
        else 
        {
            /* Read from the device */
            ram_disk_device_read(start_sector + sector_offset, buffer, sectors);
        }
        sector_offset += sectors;
    }
    if (sector_offset != sector_cnt)
    {
        printk(KERN_ERR "rb: bio info doesn't match with the request info");
        ret = -EIO;
    }
 
    return ret;
}
 

//Represents a block I/O request for us to execute
static void rb_request(struct request_queue *q)
{
    struct request *req;
    int ret;
 
    /* Gets the current request from the dispatch queue */
    while ((req = blk_fetch_request(q)) != NULL)
    {
        ret = rb_transfer(req);
        __blk_end_request_all(req, ret);
    }
}

/*
 * These are the file operations that performed on the ram block device
 */

static struct block_device_operations rb_fops =
{
    .owner = THIS_MODULE,
    .open = rb_open,
    .release = rb_close
};
 
/*
 * This is the registration and initialization section of the ram block device
 * driver
 */
static int __init rb_init(void)
{
    int ret;
 
    /* Set up our RAM Device */
    if ((ret = ram_disk_device_init()) < 0)
    {
        return ret;
    }
    rb_dev.size = ret;
 
    /* Get Registered */
    rb_major = register_blkdev(rb_major, "rb");
    if (rb_major <= 0)
    {
        printk(KERN_ERR "rb: Unable to get Major Number\n");
        ram_disk_divce_free();
        return -EBUSY;
    }
 
    /* Get a request queue (here queue is created) */
    spin_lock_init(&rb_dev.lock);
    rb_dev.rb_queue = blk_init_queue(rb_request, &rb_dev.lock);
    if (rb_dev.rb_queue == NULL)
    {
        printk(KERN_ERR "rb: blk_init_queue failure\n");
        unregister_blkdev(rb_major, "rb");
        ram_disk_divce_free();
        return -ENOMEM;
    }
 
    /*
     * Add the gendisk structure
     * By using this memory allocation is involved,
     * the minor number we need to pass bcz the device
     * will support this much partitions
     */
    rb_dev.rb_disk = alloc_disk(RB_MINOR_CNT);
    if (!rb_dev.rb_disk)
    {
        printk(KERN_ERR "rb: alloc_disk failure\n");
        blk_cleanup_queue(rb_dev.rb_queue);
        unregister_blkdev(rb_major, "rb");
        ram_disk_divce_free();
        return -ENOMEM;
    }
 
    /* Setting the major number */
    rb_dev.rb_disk->major = rb_major;
    /* Setting the first mior number */
    rb_dev.rb_disk->first_minor = RB_FIRST_MINOR;
    /* Initializing the device operations */
    rb_dev.rb_disk->fops = &rb_fops;
    /* Driver-specific own internal data */
    rb_dev.rb_disk->private_data = &rb_dev;
    rb_dev.rb_disk->queue = rb_dev.rb_queue;
    /*
     * You do not want partition information to show up in
     * cat /proc/partitions set this flags
     */
    //rb_dev.rb_disk->flags = GENHD_FL_SUPPRESS_PARTITION_INFO;
    sprintf(rb_dev.rb_disk->disk_name, "rb");
    /* Setting the capacity of the device in its gendisk structure */
    set_capacity(rb_dev.rb_disk, rb_dev.size);
 
    /* Adding the disk to the system */
    add_disk(rb_dev.rb_disk);
    /* Now the disk is "live" */
    printk(KERN_INFO "rb: Ram Block driver initialised (%d sectors; %d bytes)\n",
        rb_dev.size, rb_dev.size * SECTOR_SIZE);
 
    return 0;
}
/*
 * This is the unregistration and uninitialization section of the ram block
 * device driver
 */
static void __exit rb_cleanup(void)
{
    del_gendisk(rb_dev.rb_disk);
    put_disk(rb_dev.rb_disk);
    blk_cleanup_queue(rb_dev.rb_queue);
    unregister_blkdev(rb_major, "rb");
    ram_disk_divce_free();
}
 
module_init(rb_init);
module_exit(rb_cleanup);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anil Kumar Pugalia <email@sarika-pugs.com>");
MODULE_DESCRIPTION("Ram Block Driver");
MODULE_ALIAS_BLOCKDEV_MAJOR(rb_major);
