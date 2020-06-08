#ifndef DEVICE_H
#define DEVICE_H

static struct miscdevice my_misc_device =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = "process_list",
	.fops = &fops
};

static struct task_struct *task;

#endif //DEVICE_H
