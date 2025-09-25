#include "mydrv.h"

static const char *color_prefixes[] = {
    "\033[1;31m", // Red
    "\033[1;32m", // Green
    "\033[1;33m", // Yellow
    "\033[1;34m", // Blue
    "\033[1;35m", // Purple
    "\033[1;36m", // Cyan
    "\033[4;31m", // Red, underline
    "\033[4;32m", // Green, underline
    "\033[4;33m", // Yellow, underline
    "\033[4;34m", // Blue, underline
    "\033[4;35m", // Purple, underline
    "\033[4;36m"  // Cyan, underline
    "\033[5;31m", // Red, flash
    "\033[5;32m", // Green, flash
    "\033[5;33m", // Yellow, flash
    "\033[5;34m", // Blue, flash
    "\033[5;35m", // Purple, flash
    "\033[5;36m"  // Cyan, flash
};
static const char *warmup_msgs[] = {
    "Author: From Beijing to Hiroshima, Professors kept saying the same thing:",
    "Author: 'Your math is too poor!'",
    "Author: But every time they said it, I had already deleted their math-heavy bullshit,",
    "Author: and the system still ran — faster, cleaner, simpler.",
};
static const char *unix_days[] = {"Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};
static const char *prof_words[] = {
    "You can't just delete that!",
    "Your math is too poor!",
    "Without the formula, it's meaningless!",
    "Go back and study linear algebra!",
    "This is not rigorous.",
    "We need publish papers!",
    "Intuition won't work here!",
    "This is not scientific research!",
    "You are running blind code!"
};
static char msg_buf[256] = {0}; static uint8_t msg_len = 0;

#define choose_random(list) list[get_cycles() % (sizeof(list) / sizeof(char *))]
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
        msg_len = sprintf(msg_buf, "\033[1;33mWarning from Prof with %s(PID=%lld):\033[0m %s%s\033[0m\n\r", p->comm, p->pid, choose_random(color_prefixes), choose_random(prof_words));
        p->signal->tty->ops->write(p->signal->tty, msg_buf, msg_len);
    }
    else
    {
        msg_len = sprintf(msg_buf, "\033[1;31mProf was ANGRY with %s(PID=%lld):\033[0m %s%s\033[0m\n\r", p->comm, p->pid, choose_random(color_prefixes), choose_random(prof_words));
        boardcast_all_tty(msg_buf, msg_len);
    }
    return 1;
}