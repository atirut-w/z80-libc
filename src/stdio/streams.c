#include <stdio.h>

static FILE __stdin = {0};
static FILE __stdout = {1};
static FILE __stderr = {2};

FILE *stdin = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;
