#include "syscalls.h"
#include <stdlib.h>

FILE _iob[OPEN_MAX] = {
    /* stdin, stdout, stderr */
    { 0, (char *)0, (char *)0, _READ | _UNBUF, 0 },
    { 0, (char *)0, (char *)0, _WRITE | _UNBUF, 1 },
    { 0, (char *)0, (char *)0, _WRITE | _UNBUF, 2 },
};
/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
        return EOF;
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) { /* no buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL) {
            return EOF; /* can't get buffer */
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag |= _EOF;
        } else {
            fp->flag |= _ERR;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
    int to_write, written;
    char uc = c;

    if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {
        return EOF;
    }

    if (fp->base == NULL && ((fp->flag & _UNBUF) == 0)) {
        /* no buffer yet */
        if ((fp->base = (char *)malloc(BUFSIZ)) == NULL) {
            /* could not allocate buffer, so try unbuffered */
            fp->flag |= _UNBUF;
        }
        fp->ptr = fp->base;
        *fp->ptr++ = c;
        fp->cnt = BUFSIZ - 1;
        return c;
    }

    if (fp->flag & _UNBUF) { /* unbuffered write */
        to_write = 1;
        if (c == EOF) {
            return EOF;
        }
        written = write(fp->fd, &uc, 1);
        fp->ptr = fp->base = NULL;
        fp->cnt = 0;
    } else {
        to_write = (int)(fp->ptr - fp->base);
        written = write(fp->fd, fp->base, to_write);
        fp->ptr = fp->base;
        fp->cnt = BUFSIZ - 1;
    }
    if (written == to_write) {
        return c;
    } else {
        fp->flag |= _ERR;
        return EOF;
    }
}

int main()
{
    int c;
    while ((c = getchar()) != 'x') {
        putchar(c);
    }
}
