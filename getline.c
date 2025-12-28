#include <stdio.h>
int getLine(char* line, int max)
{
    int c, i;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    return i;
}
