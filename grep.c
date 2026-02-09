// Let's copy grep yea
/**
 * Stuff I want to recreate
 * Basic functionality:
 * - grep pattern filename
 *
 * Once that works, add support for multiple filenames
 * - grep pattern filename1 filename2
 * Once that works, add line numbers
 * - grep pattern filenames -n
 * Once that works too, add context
 * - grep pattern filenames -C 2
 */
#include <stdio.h>
#include <stdlib.h>

void
check_file(FILE *fIn, const char *pattern)
{
    for (;;) {
    }
}

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "%s: Wrong number of arguments", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern = argv[1];

    for (int i = 2; i < argc; i++) {
        FILE *fIn = fopen(argv[i], "rb");
        if (!fIn) {
            fprintf(stderr, "%s: Could not open %s", argv[0], argv[i]);
            return EXIT_FAILURE;
        }

        check_file(fIn, pattern);

        fclose(fIn);
    }

    return EXIT_SUCCESS;
}
