#include <linux/module.h>   // Core header for loading LKMs into the kernel
#include <linux/kernel.h>   // Contains types, macros, functions for the kernel
#include <linux/init.h>     // Macros used to mark up functions e.g. __init __exit

#define DEVICE_NAME "my_chardev"

static int my_open()(struct inode *, struct file *)
{

}

static int my_release(struct inode *, struct file *);
static int my_read(struct file *, char __user *, size_t, loff_t *);
static int my_write(struct file *, const char __user *, size_t, loff_t *);

// Module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux kernel module example");
MODULE_VERSION("1.0");

// Function that runs when the module is loaded
static int __init hello_init(void) {
    printk(KERN_INFO "Hello, Kernel World!\n");
    return 0;
}

// Function that runs when the module is removed
static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, Kernel World!\n");
}

// Register entry and exit points
module_init(hello_init);
module_exit(hello_exit);
