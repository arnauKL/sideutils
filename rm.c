#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "rm: No arguments given\n");
        return EXIT_FAILURE;
    }

    /*
     * So, how do we remove files? Let's check out the man page for `unlink`
     * Can't find them on my system so I'll find them online
     * */

    for (int i = 1; i < argc; i++) {
        if (unlink(argv[i]) != 0)
            fprintf(stderr, "rm: unable to delete the file '%s': %s\n", argv[i],
                    strerror(errno));
    }

    return 0;
}
