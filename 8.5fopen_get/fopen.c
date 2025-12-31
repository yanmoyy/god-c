#include "stdio.h"
#include "syscalls.h"
#include <fcntl.h>
#define PERMS 0666 /* RW for owner, group, others */

FILE *_fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if ((fp->flag & (_READ | _WRITE)) == 0) {
            break; /* found free slot */
        }
    }
    if (fp >= _iob + OPEN_MAX) { /* no free slots */
        return NULL;
    }
    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
    }
}
