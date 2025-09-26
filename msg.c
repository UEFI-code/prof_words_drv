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
static char *unix_days[] = {"Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};
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

static __inline void gen_warn_msg(struct task_struct *p)
{
    msg_len = sprintf(msg_buf, "\033[1;33mWarning from Prof with %s(PID=%lld):\033[0m %s%s\033[0m\n\r", p->comm, p->pid, choose_random(color_prefixes), choose_random(prof_words));
}

static __inline void gen_angry_msg(struct task_struct *p)
{
    msg_len = sprintf(msg_buf, "\033[1;31mProf was ANGRY with %s(PID=%lld):\033[0m %s%s\033[0m\n\r", p->comm, p->pid, choose_random(color_prefixes), choose_random(prof_words));
}