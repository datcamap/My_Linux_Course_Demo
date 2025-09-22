#include <linux/module.h>   // Core header for loading LKMs into the kernel
#include <linux/kernel.h>   // Contains types, macros, functions for the kernel
#include <linux/init.h>     // Macros used to mark up functions e.g. __init __exit
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEVICE_NAME "my_char_dev"
#define CLASS_NAME "my_char_class"
#define KBUFFER_CAP 4096

// Module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux kernel module example");
MODULE_VERSION("1.0");

static const char *my_str = "Hello! This is my demo driver!\n";

struct my_dev {
    dev_t devno;
    size_t kbuf_len;
    char *kmalloc_ptr;
    struct cdev my_cdev;
    struct class *my_class;
    struct device *my_device;
} char_dev;

static int my_open(struct inode *, struct file *);
static int my_release(struct inode *, struct file *);
static ssize_t my_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char __user *, size_t, loff_t *);

static struct file_operations fops =
{
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write
};

static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO DEVICE_NAME ": open\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO DEVICE_NAME ": release\n");
    return 0;
}

static ssize_t my_read(struct file *file, char __user *user_buf, size_t size, loff_t *offset)
{
    ssize_t not_copy;

    if (*offset >= char_dev.kbuf_len) {
        return 0;
    }

    not_copy = (ssize_t)copy_to_user(user_buf, my_str, strlen(my_str));
    *offset += strlen(my_str);

    return 1;
}

static ssize_t my_write(struct file *file, const char __user *user_buf, size_t size, loff_t *offset)
{
    return 0;
}

// Function that runs when the module is loaded
static int __init hello_init(void)
{   
    char_dev.kmalloc_ptr = (char *)kmalloc(KBUFFER_CAP, GFP_KERNEL);
    if (char_dev.kmalloc_ptr == NULL) {
        printk(KERN_ERR "Cannot allocate kernel buffer.\n");
        return -ENOMEM;
    }
    char_dev.kbuf_len = 0;

    if (alloc_chrdev_region(&char_dev.devno, 0, 1, DEVICE_NAME) < 0) {
        printk(KERN_ERR "Cannot allocate kernel device.\n");
        goto fail_alloc;
    }
    cdev_init(&char_dev.my_cdev, &fops);
    if (cdev_add(&char_dev.my_cdev, char_dev.devno, 1)) {
        printk(KERN_ERR "Failed to add device.\n");
        goto fail_cdev;
    }

    if ((char_dev.my_class = class_create(CLASS_NAME)) == NULL) {
        printk(KERN_ERR "Cannot create class.\n");
        goto fail_class;
    }

    if (device_create(char_dev.my_class, NULL, char_dev.devno, NULL, DEVICE_NAME) == NULL) {
        printk(KERN_ERR "Cannot create device.\n");
        goto fail_device;
    }
    
    printk(KERN_INFO "Hello, Kernel World!\n");
    return 0;

    fail_device:
        class_destroy(char_dev.my_class);
    fail_class:
        cdev_del(&char_dev.my_cdev);
    fail_cdev:
        unregister_chrdev_region(char_dev.devno, 1);
    fail_alloc:
        kfree(char_dev.kmalloc_ptr);
    return -1;
}

// Function that runs when the module is removed
static void __exit hello_exit(void)
{
    device_destroy(char_dev.my_class, char_dev.devno);
    class_destroy(char_dev.my_class);
    cdev_del(&char_dev.my_cdev);
    unregister_chrdev_region(char_dev.devno, 1);
    kfree(char_dev.kmalloc_ptr);
    printk(KERN_INFO "Goodbye, Kernel World!\n");
}

// Register entry and exit points
module_init(hello_init);
module_exit(hello_exit);
