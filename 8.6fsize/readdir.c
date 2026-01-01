#include "dirent.h"
#include <string.h>
#include <sys/dirent.h>
#include <unistd.h>

/* readdir: read a directory entry */
Dirent *readdir(DIR *dp)
{
    struct dirent dirbuf; /* local directory structure */
    static Dirent d;

    while (read(dp->fd, (char *)&dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0) { /* slot not in use */
            continue;
        }
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, NAME_MAX);
        d.name[NAME_MAX] = '\0'; /* ensure null termination */
        return &d;
    }
    return NULL;
}
