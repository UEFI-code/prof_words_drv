#include "mydrv.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SuperHacker UEFI");
MODULE_DESCRIPTION("A drv that simulates your acdaemic prof's words");
MODULE_VERSION("1.0");

struct task_struct *worker_task;

static void worker(void)
{
    egg();
    while(!kthread_should_stop())
    {
        ssleep(1);
        struct task_struct *p; 
        for_each_process(p)
        {
            if (p->signal) regist_tty(p->signal->tty);
            egg2(p);
        }
    }
    printk(KERN_INFO "Prof Words Worker Thread Stopped\n");
}

static int __init prof_words_init(void)
{
    printk(KERN_INFO "Prof Words Driver Initialized\n");
    worker_task = kthread_create((void *)worker, NULL, "prof_words_worker");
    wake_up_process(worker_task);
    return 0;
}

static void __exit prof_words_exit(void)
{
    kthread_stop(worker_task);
    printk(KERN_INFO "Prof Words Driver Exited\n");
}

module_init(prof_words_init);
module_exit(prof_words_exit);