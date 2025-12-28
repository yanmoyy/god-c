#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getLine(char* line, int max);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char* argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') // for each option
        while ((c = *++argv[0])) // for each char in option
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
    printf("argc: %d\n", argc);
    if (argc != 1)
        printf("Usage: find -x -n pattern\n");
    else
        while (getLine(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    printf("found: %d\n", found);
    return found;
}

int getLine(char* line, int max)
{
    int c, i;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    return i;
}
