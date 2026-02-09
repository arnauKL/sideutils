#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // check file stat
#include <unistd.h>

// The `cat` I'll make takes in a series of filenames and prints the contents
// out to stdout

// This could be checked using fstat on the file descriptor and get st_blksize
// I'll use 4 KiB, tends to match the page size of the OS so no alignment is
// needed
#define BUFFER_SIZE 4096

int
main(int argc, const char *argv[])
{
    // This is not the real behaviour but whatever
    if (argc < 2) {
        fprintf(stderr, "%s: not enough arguments\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        char buf[BUFFER_SIZE];

        FILE *fptr = fopen(argv[i], "rb");
        // why "rb" over "r": "rb" does nothing to the characters ("r" can)

        if (!fptr) {
            fprintf(stderr, "%s: there was an error accessing %s: %s", argv[0], argv[i],
                    strerror(errno));
            continue;
        }

        /**
         * fgetc -> no: a function call for each character is unreasonable.
         * fgets / fscanf -> meant for formatted input/parsing, not the case.
         * will use fgets for now anyway.
         * stdio.h functions are buffered */
        // fgets stops at \n or \0 so no reading binary files

        int bytes_read = 0;
        while ((bytes_read = fread(buf, sizeof(char), sizeof(buf), fptr)) > 0) {
            ssize_t bytes_written = fwrite(buf, sizeof(char), bytes_read, stdout);
            if (bytes_written < bytes_read) {
                fprintf(stderr, "%s: there was an error writing to stdout: %s", argv[0],
                        strerror(errno));
            }
        }

        fclose(fptr);
    }

    return EXIT_SUCCESS;
}
