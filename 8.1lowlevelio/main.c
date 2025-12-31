#include <stdio.h>
#include <unistd.h>

int main2()
{
    char buf[BUFSIZ];
    int n;

    while ((n = read(0, buf, BUFSIZ)) > 0) {
        write(1, buf, n);
    }
    return 0;
}
