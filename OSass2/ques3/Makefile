obj-m += custom_syscall_module.o

all:
        compile load print

compile:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
        $(CC) ques3.c -o ques3

clean:
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
        rm -f ques3

load:
        insmod custom_syscall_module.ko

unload:
        rmmod custom_syscall_module.ko

print:
        dmesg | tail -n 20

.PHONY:
        all compile clean load unload print
