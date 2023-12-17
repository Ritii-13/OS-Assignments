#include <linux/sched/signal.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("2022036_2022408");
MODULE_DESCRIPTION("Custom System Call Module");

// Define the custom system call number
#define MY_CUSTOM_SYSCALL_NUMBER 333

// Function to count the number of running processes
static long count_running_processes(void) {
    struct task_struct *task;
    long count = 0;
    printk("--------------------------------");
    // Traverse the task list
    for_each_process(task) {
        if (task->state == TASK_RUNNING) {
            count++;
        }
    }

    return count;
}

// Define the custom system call
// static long sys_my_custom_syscall(void) {
//     long count = count_running_processes();
//     printk(KERN_INFO "Number of running processes: %ld\n", count);
//     return count;
// }

// Module initialization
static int __init init_custom_syscall_module(void) {
    printk(KERN_INFO "Custom System Call Module Loaded\n");
    printk("-------------------------------------");

    long count = count_running_processes();
    printk("-------------------------------------");
    printk(KERN_INFO "Number of running processes: %ld\n", count);

    // Register the custom system call
    // if (register_syscall(MY_CUSTOM_SYSCALL_NUMBER, sys_my_custom_syscall) != 0) {
    //    printk(KERN_ERR "Failed to register custom syscall\n");
    //     return -EFAULT;
    // }

    return 0;
}

// Module cleanup
static void __exit exit_custom_syscall_module(void) {
    printk(KERN_INFO "Custom System Call Module Unloaded\n");
    printk("-------------------------------------");

    // Unregister the custom system call
    // unregister_syscall(MY_CUSTOM_SYSCALL_NUMBER);
}

module_init(init_custom_syscall_module);
module_exit(exit_custom_syscall_module);