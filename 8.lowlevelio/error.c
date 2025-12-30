#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* error: print an error message and die */
void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vprintf(stderr, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
