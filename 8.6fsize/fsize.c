#include <stdio.h>
#include <sys/stat.h>

// int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/* fsize: print the name of file "name" */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    printf("%8lld bytes %s\n", stbuf.st_size, name);
}
