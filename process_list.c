#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include "variable.h"
#include "operation.h"
#include "file_operation.h"
#include "device.h"
#include <linux/uaccess.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");

static int __init processchar_init(void)
{
  minorNumber = misc_register(&my_misc_device);
	if (minorNumber<0)
	{
		printk(KERN_ALERT "Process_list failed to register a minor number\n");
		misc_deregister(&my_misc_device);
		return minorNumber;
	}
	printk(KERN_INFO "Process_list registered correctly with major number: 10 and minor number: %d\n", minorNumber);
	return 0;
}

static void __exit processchar_exit(void)
{
	misc_deregister(&my_misc_device);
	printk(KERN_INFO "Process_list saying Goodbye from the LKM!\n");
}

static int dev_open(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "Process_list has been opened\n");
	return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
	int error_count=0;
	for_each_process(task)
	{
                if (task->state == 0){sprintf(state_str, "TASK_RUNNING");}
                else if (task->state == 1){sprintf(state_str, "TASK_INTERRUPTIBLE");}
                else if (task->state == 2){sprintf(state_str, "TASK_UNINTERRUPTIBLE");}
                else {sprintf(state_str, "OTHER");}

		sprintf(kernel_buffer + strlen(kernel_buffer), "PID=%d  PPID=%d  CPU=%d  STATE=%s\n", task->pid, task->real_parent->pid, task_cpu(task), state_str);
		size_of_buffer = strlen(kernel_buffer);
	}
	error_count = copy_to_user(buffer, kernel_buffer, size_of_buffer);
	return error_count;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "Process_list successfully closed\n");
	return 0;
}

module_init(processchar_init);
module_exit(processchar_exit);
