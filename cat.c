#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// `cat` takes in a series of filenames and prints them out to stdout

int
main(int argc, const char *argv[])
{

    // This is not the real behaviour but whatever
    if (argc < 2) {
        fprintf(stderr, "%s: not enough arguments\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fptr = fopen(argv[i], "r");
        // TODO: why "r" or "rb" ?

        if (!fptr) {
            fprintf(stderr, "%s: there was an error accessing %s: %s", argv[0],
                    argv[i], strerror(errno));
            return EXIT_FAILURE;
        }

        // File opened, pritnt contents

        return EXIT_SUCCESS;
    }
}
