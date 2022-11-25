#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int p[2];
    pipe(p);
    char r_buf[10];
    char w_buf[10];

    if(fork() == 0)
    {
        read(p[0], r_buf, 1);
        close(p[0]);
        printf("%d: received ping\n", getpid());
        write(p[1], w_buf, 1);
        close(p[1]);
        exit(0);
    }
    else
    {
        write(p[1], w_buf, 1);
        close(p[1]);
        read(p[0], r_buf, 1);
        close(p[0]);
        printf("%d: received pong\n", getpid());
        exit(0);
    }

    exit(0);
}
