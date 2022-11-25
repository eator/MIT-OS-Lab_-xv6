#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

const char* para_err = "sleep need an integer parameter\n";
int
main(int argc, char *argv[])
{

    if(argc<2)
    {
        write(2, para_err, strlen(para_err));
        exit(1);
    }

    int sleep_t = atoi(argv[1]);

    sleep(sleep_t);
    
    exit(0);
}
