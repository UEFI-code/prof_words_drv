# Multi-file module
obj-m += prof_words.o
prof_words-objs := main.o egg.o

# Get the kernel version and build directory
KVERSION = $(shell uname -r)
KDIR = /lib/modules/$(KVERSION)/build

# Default target
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Clean target
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

# Install target (load the module)
install:
	sudo insmod prof_words.ko

# Uninstall target (unload the module)
uninstall:
	sudo rmmod prof_words

.PHONY: all clean install uninstall dmesg test
