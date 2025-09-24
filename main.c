#include "mydrv.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SuperHacker UEFI");
MODULE_DESCRIPTION("A drv that simulates your acdaemic prof's words");
MODULE_VERSION("1.0");

struct task_struct *worker_task;
static uint8_t running = 0;

static void worker(void)
{
    printk(KERN_INFO "Prof Words Worker Thread Started\n");
    while(running)
    {
        ssleep(5);
        // chk prev task
    }
    printk(KERN_INFO "Prof Words Worker Thread Stopped\n");
}

static int __init prof_words_init(void)
{
    printk(KERN_INFO "Prof Words Driver Initialized\n");
    worker_task = kthread_create((void *)worker, NULL, "prof_words_worker");
    running = 1;
    wake_up_process(worker_task);
    return 0;
}

static void __exit prof_words_exit(void)
{
    running = 0;
    printk(KERN_INFO "Prof Words Driver Exited\n");
}

module_init(prof_words_init);
module_exit(prof_words_exit);