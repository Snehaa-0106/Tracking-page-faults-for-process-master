#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

static struct file_operations fops =
{
	.open = dev_open,
        .read = dev_read,
        .release = dev_release,
};

#endif //FILE_OPERATION_H
