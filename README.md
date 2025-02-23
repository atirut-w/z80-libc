# Z80 Libc
A standard C library for the Z80 processor. This is to be used with [an LLVM backend for the Z80](https://github.com/atirut-w/llvm-project).

## POSIX
While the library is designed to be as environment-agnostic as possible, some parts of the library (notably the allocator and I/O) require *some* type of interaction with the environment. I have opted to use POSIX as the interface for this interaction. This means that some parts of the library will require you to implement some POSIX functions in order to use them. If you use them without implementing them, you will get a linker error.
