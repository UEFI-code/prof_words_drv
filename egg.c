#include <linux/time.h>
#define xclock_sec ktime_get_real_seconds()
#define ktime_sec ktime_get_seconds()
#include <linux/tty.h>

static const char *unix_days[] = {"Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};
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

#define choose_random(list) list[get_cycles() % (sizeof(list) / sizeof(char *))]
static __inline void tty_writer(struct tty_struct *tty, const char *buf, size_t len)
{
    switch(tty->driver->type) {
        case TTY_DRIVER_TYPE_SERIAL:
            for (size_t i = 0; i < len; i++)
                tty->ops->put_char(tty, buf[i]); // no flush, to prevent hardware corruption
            break;
        case TTY_DRIVER_TYPE_CONSOLE:
        case TTY_DRIVER_TYPE_PTY:
            if (tty && tty->ops && tty->ops->write)
                tty->ops->write(tty, buf, len);
            break;
        default:
            pr_alert("tty_writer: unknown %s type %d\n", tty->name, tty->driver->type);
            break;
    }
}
static struct tty_struct *tty_list[128] = {0};
static int tty_count = 0;
__inline void register_tty(struct tty_struct *tty)
{
    if (tty_count >= 128) return;
    if (!tty) return;
    for (int i = 0; i < tty_count; i++)
        if (tty_list[i] == tty) return;
    tty_list[tty_count++] = tty;
}
static __inline void boardcast_all_tty(const char *buf, size_t len)
{
    for (int i = 0; i < tty_count; i++)
        tty_writer(tty_list[i], buf, len);
}

void egg(void)
{
    static uint8_t shown = 0;
    if (shown) return;
    pr_alert("Author: From Beijing to Hiroshima, Professors kept saying the same thing:\n");
    pr_alert("Author: 'Your math is too poor!'\n");
    pr_alert("Author: But every time they said it, I had already deleted their math-heavy bullshit,\n");
    pr_alert("Author: and the system still ran — faster, cleaner, simpler.\n");
    if (xclock_sec)
        pr_alert("!!! Happy %s !!!\n", unix_days[(xclock_sec/86400)%7]);
    else
        pr_alert("!!! Happy ???Day, time unknown 233 !!!\n");
    shown = 1;
}

static char msg_buf[256] = {0}; static uint8_t msg_len = 0;
struct tty_driver *driver;

void egg2(struct task_struct *p)
{
    static uint64_t last_yield = 0;
    if (ktime_sec-last_yield<30) return;
    if (p->utime%255 < 233) return;
    if (p->signal && p->signal->tty)
    {
        msg_len = sprintf(msg_buf, "\033[1;33mWarning from Prof with %s(PID=%lld):\033[0m %s%s\033[0m\n\r", p->comm, p->pid, choose_random(color_prefixes), choose_random(prof_words));
        tty_writer(p->signal->tty, msg_buf, msg_len);
    }
    else
    {
        msg_len = sprintf(msg_buf, "\033[1;31mProf was ANGRY with %s(PID=%lld):\033[0m %s%s\033[0m\n\r", p->comm, p->pid, choose_random(color_prefixes), choose_random(prof_words));
        boardcast_all_tty(msg_buf, msg_len);
    }
    last_yield = ktime_sec;
}