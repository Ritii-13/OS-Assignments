# Custom System Call Module and Makefile

## Overview

This project consists of a custom system call module for the Linux kernel, which can be invoked to retrieve the count of running processes within the Linux kernel and a Makefile for compiling, loading, unloading, and printing kernel logs.

### Custom System Call Module

The custom system call module defines a new system call that counts the number of running processes in the Linux kernel. When invoked, the system call prints the count to the kernel logs. This module is implemented in the file `custom_syscall_module.c`.

#### Code Description

The custom system call module code (`custom_syscall_module.c`) includes the following components:

### `count_running_processes` Function

The `count_running_processes` function iterates through the list of tasks in the kernel's task list and counts the number of processes that are currently in the `TASK_RUNNING` state. It logs separator lines to the kernel log before and after its execution.

## Module Initialization and Cleanup

The module defines initialization and cleanup functions:

- `init_custom_syscall_module`: This function is executed when the module is loaded into the kernel. It logs messages indicating the module's loading, performs the counting operation, and logs the count to the kernel log.
  
- `exit_custom_syscall_module`: This function is executed when the module is unloaded from the kernel. It logs a message indicating the module's unloading.


### Makefile

The Makefile provided in this project simplifies the compilation, loading, unloading, and kernel log viewing processes for the custom system call module. It includes the following targets:

- `all`: Compiles the custom system call module and a user program, loads the module, and prints the kernel logs.
- `compile`: Compiles only the custom system call module and the user program.
- `clean`: Cleans up compiled files.
- `load`: Loads the custom system call module into the kernel.
- `unload`: Unloads the custom system call module from the kernel.
- `print`: Displays the last 20 lines of the kernel logs.

## Usage

Follow these steps to use the provided Makefile and custom system call module:

1. Place the `ques3.c` file (the custom system call module code) and the makefile in the same directory.

2. Use the following commands to interact with the module:

   - `make all`: Compiles the module, loads it, and prints kernel logs.
   - `make compile`: Compiles only the module and the user program.
   - `make clean`: Cleans up compiled files.
   - `make load`: Loads the module into the kernel.
   - `make unload`: Unloads the module from the kernel.
   - `make print`: Displays the last 20 lines of the kernel logs.

4. Review the kernel logs using the `make print` command to see the output of the custom system call.

## Important Notes

- The code may or may not execute properly depending on the system and version being used.
