#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/io.h>
#include <linux/kthread.h>
#include <linux/delay.h>

extern void regist_tty(struct tty_struct *tty);
extern void egg(void);
extern void egg2(struct task_struct *p);