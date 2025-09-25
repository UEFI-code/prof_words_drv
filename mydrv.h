#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/tty.h>

#define xclock_sec ktime_get_real_seconds()
#define ktime_sec ktime_get_seconds()

extern uint16_t tty_count;
extern void regist_tty(struct tty_struct *tty);
extern void egg(void);
extern uint8_t egg2(struct task_struct *p);