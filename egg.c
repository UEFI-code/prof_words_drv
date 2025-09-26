#include "mydrv.h"
#include "msg.c"

struct tty_struct *tty_list[128] = {0}; uint16_t tty_count = 0;
void regist_tty(struct tty_struct *tty)
{
    if (!tty || !tty->driver || !tty->ops) return;
    if (tty_count >= sizeof(tty_list)/sizeof(char *)) return;
    for (int i = 0; i < tty_count; i++)
        if (tty_list[i] == tty) return;
    tty_list[tty_count++] = tty;
    //printk(KERN_INFO "Registered TTY: %s, total %d\n", tty->name, tty_count);
}
static __inline void boardcast_all_tty(const char *buf, size_t len)
{
    for (int i = 0; i < tty_count; i++) tty_list[i]->ops->write(tty_list[i], buf, len);
}

void egg(void)
{
    for (int i = 0; i < sizeof(warmup_msgs)/sizeof(char *); i++)
    {
        msg_len = sprintf(msg_buf, "%s%s\033[0m\n\r", choose_random(color_prefixes), warmup_msgs[i]);
        boardcast_all_tty(msg_buf, msg_len);
    }
    msg_len = sprintf(msg_buf, "%s!!! Happy %s !!!\033[0m\n\r", choose_random(color_prefixes), unix_days[(xclock_sec/86400)%7]);
    boardcast_all_tty(msg_buf, msg_len);
}
uint8_t egg2(struct task_struct *p)
{
    if (p->utime%255 < 233) return 0;
    if (p->signal && p->signal->tty)
    {
        gen_warn_msg(p);
        p->signal->tty->ops->write(p->signal->tty, msg_buf, msg_len);
    }
    else
    {
        gen_angry_msg(p);
        boardcast_all_tty(msg_buf, msg_len);
    }
    return 1;
}