#pragma once

#define EXIT_SUCCESS (0)
#define EXIT_FAILURE (1)

/* Causes normal program termination with cleaning up */
void exit(int status);

/* Registers a function to be called on `exit()` invocation */
int atexit(void (*func)(void));
