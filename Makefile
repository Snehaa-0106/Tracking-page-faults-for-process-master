obj-m+=process_list.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) user_program.c -o process_list
insert:
	sudo insmod process_list.ko
execute:
	sudo ./process_list
remove:
	sudo rmmod process_list
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm process_list
