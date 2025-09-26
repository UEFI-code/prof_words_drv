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
static const char *common_fg[] = {
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
static const char *common_bg[] = {
    "Electricity is NOT free !!!",
    "Do you know how much CO2 you are producing?!",
    "Who runs this blind code without any formula?",
    "Do you ALL think electricity is free!?",
    "Don't let me catch the author of this blind code!",
    "You ALL have moral problems to have this garbage in the system!",
    "You ALL should be ashamed of yourselves!",
};
static const char *script_fg[] = {
    "Shut this stupid script down! We need publish papers!",
    "How many times I told you that you are running BLIND code?",
    "You are running scripts without theories background!",
    "Your linear algebra is too poor!",
    "This is Script kiddie work!",
};
static const char *script_bg[] = {
    "Who allows you to run this stupid script in the background?",
    "Without formulas proven, your script is just garbage!",
    "You are polluting the environment with your blind script!",
    "You are ALL irresponsible to run this blind script overnight!",
};
static const char *miner_fg[] = {
    "You want be kick out?! You have moral problem!",
    "You are stealing electricity with this mining code!",
    "You are polluting the environment with this mining code!",
    "Without theories background, go Aliexpress and resell is more suitable for you!",
    "You can't actually get profit, but just WASTING our resources!",
};
static const char *miner_bg[] = {
    "Who is fucking mining in the background?!",
    "You ALL have moral problems to run this mining code!",
    "You ALL should be ashamed of yourselves to run this mining code!",
    "Who did this?? He should be fired!",
    "You can profit a Lolipop after you mining for 1 week!!",
};
static const char *bitcoin_fg[] = {
    "Are you fucking debugging Bitcoin code again?!",
    "Without theories background, go Aliexpress and resell is more suitable for you!",
    "You think you are Satoshi Nakamoto?",
};
static const char *bitcoin_bg[] = {
    "Who is fucking running Bitcoin code in the background?!",
    "You ALL think you are Satoshi Nakamoto?",
    "You ALL dreaming to be a pool owner?",
};
static const char *compiler_fg[] = {
    "You are building skyscrapers without theory background...",
    "You are wasting our CPU cycles to build blind code!",
    "You have moral problems to waste our resources like this!",
    "Don't think you are Linus Torvalds!",
};
static const char *compiler_bg[] = {
    "Who allowed you to build blind code in the background like this?!",
    "You ALL copy-and-paste code without understanding it!",
    "You ALL proud of yourself to build blind code overnight like this?",
};
static const char *shell_fg[] = {
    "You are wasting time here...",
    "You should study formulas before touching the terminal!",
    "Don't be a script kiddie!",
};
static const char *editor_fg[] = {
    "Review theories carefully!",
    "Learn formula carefully.",
    "You fucking writing blind code again?!",
    "Don't tamper our system with your blind code!",
};
static const char *debugger_fg[] = {
    "You are debugging blind code without theory background...",
    "You think you are Steve Jobs?",
    "This is NOT scientific research!",
    "Use academic voice, or you cannot publish paper!",
    "You think you can figure out the bug without understanding the theory?",
};
static const char *git_fg[] = {
    "You are cloning blind code without theory background...",
    "Script kiddie always doing something like this!",
    "We need publish papers! Go back and study theory!",
};
static const char *cron_bg[] = {
    "Who set this fucking cron job?",
    "You ALL need go back and study Bayes theorem!",
    "Without Bayes theorem, the automation is just cheating!",
};
static char msg_buf[256] = {0}; static uint8_t msg_len = 0;

#define choose_random(list) list[get_cycles() % (sizeof(list) / sizeof(char *))]

static __inline void gen_warn_msg(struct task_struct *p)
{
    char *prof_word = choose_random(common_fg);
    if (strstr(p->comm, "py") || strstr(p->comm, "java") || strstr(p->comm, "ruby")) {
        prof_word = choose_random(script_fg);
    } else if (strstr(p->comm, "xmrig") || strstr(p->comm, "miner")) {
        prof_word = choose_random(miner_fg);
    } else if (strstr(p->comm, "bitcoin")) {
        prof_word = choose_random(bitcoin_fg);
    } else if (strstr(p->comm, "cc") || strstr(p->comm, "make")) {
        prof_word = choose_random(compiler_fg);
    } else if (strstr(p->comm, "sh")) {
        prof_word = choose_random(shell_fg);
    } else if (strstr(p->comm, "vi") || strstr(p->comm, "nano")) {
        prof_word = choose_random(editor_fg);
    } else if (strstr(p->comm, "db")) {
        prof_word = choose_random(debugger_fg);
    } else if (strstr(p->comm, "git")) {
        prof_word = choose_random(git_fg);
    }
    msg_len = sprintf(msg_buf, "\033[1;33mWarning from Prof with %s(PID=%lld):\033[0m %s%s\033[0m\n\r", p->comm, p->pid, choose_random(color_prefixes), prof_word);
}
static __inline void gen_angry_msg(struct task_struct *p)
{
    char *prof_word = choose_random(common_bg);
    if (strstr(p->comm, "py") || strstr(p->comm, "java") || strstr(p->comm, "ruby")) {
        prof_word = choose_random(script_bg);
    } else if (strstr(p->comm, "xmrig") || strstr(p->comm, "miner")) {
        prof_word = choose_random(miner_bg);
    } else if (strstr(p->comm, "bitcoin")) {
        prof_word = choose_random(bitcoin_bg);
    } else if (strstr(p->comm, "cc") || strstr(p->comm, "make")) {
        prof_word = choose_random(compiler_bg);
    } else if (strstr(p->comm, "cron")) {
        prof_word = choose_random(cron_bg);
    }
    msg_len = sprintf(msg_buf, "\033[1;31mProf was ANGRY with %s(PID=%lld):\033[0m %s%s\033[0m\n\r", p->comm, p->pid, choose_random(color_prefixes), prof_word);
}