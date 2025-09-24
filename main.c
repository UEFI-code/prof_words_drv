#include "mydrv.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SuperHacker UEFI");
MODULE_DESCRIPTION("A drv that simulates your acdaemic prof's words");
MODULE_VERSION("1.0");

struct task_struct *worker_task;

static __inline void scan_ttys(void)
{
    tty_count = 0; // clean all tty, as they may invalid at any time
    struct task_struct *p; for_each_process(p)
        if (p->signal) regist_tty(p->signal->tty);
}

static void worker(void)
{
    scan_ttys();
    egg();
    while(!kthread_should_stop())
    {
        ssleep(1);
        scan_ttys();
        struct task_struct *p; for_each_process(p) egg2(p);
    }
    printk(KERN_INFO "Prof Words Worker Thread Stopped\n");
}

static __init int prof_words_init(void)
{
    printk(KERN_INFO "Prof Words Driver Initialized\n");
    worker_task = kthread_create((void *)worker, NULL, "prof_words_worker");
    wake_up_process(worker_task);
    return 0;
}

static __exit void prof_words_exit(void)
{
    kthread_stop(worker_task);
    printk(KERN_INFO "Prof Words Driver Exited\n");
}

module_init(prof_words_init);
module_exit(prof_words_exit);