#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

// man 3 fstat
// find pagesize of my OS
// WIP

int
main()
{
    struct stat buffer;
    int status;

    int fildes = 0;

    fildes = open("/home/cnd/mod1", O_RDWR);
    status = fstat(fildes, &buffer);

    printf("%d", buffer.PAGE_SIZE);
    return 0;
}
