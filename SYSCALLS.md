# List of supported system calls for programs
Keep in mind that programs run in kernel mode and that you can do whatever you want. These are just for your convenience
Write the syscall number in %eax, any other parameter in %ebx, %ecx, %edx, %rdi, %rsi and call `int 0x80`

The number of the syscall in this list is the value you need to write in %eax

1. Exit: quits the running program returning an error code (an integer in %ebx)
2. Write: Writes the string pointed by %ecx in the file descriptor %ebx and of length %edx. **WARN**: Right now only writing to the terminal is implemented, so you can only put `1` in `%ebx`
3. Yield: Ends the time slice of the calling process instantly.