# Z80 Libc
A standard C library for the Z80 processor. This is to be used with [an LLVM backend for the Z80](https://github.com/atirut-w/llvm-project).

## Platform Glue
Depending on what part of the library you are using, you may need to implement some platform-specific functions. These functions emulate POSIX-style system calls. The following functions are required by some parts of the library:

- `void __exit(int status)`: Exit the program with the given status.
- `void __read(int fd, void *buf, size_t count)`: Read `count` bytes from the file descriptor `fd` into `buf`.
- `void __write(int fd, const void *buf, size_t count)`: Write `count` bytes from `buf` to the file descriptor `fd`.
- `void __brk(void *addr)`: Set the program break to `addr`.
- `void __sbrk(int increment)`: Increment the program break by `increment`.

If you're not sure if you need to implement a function, just wait until you get a linker error.
