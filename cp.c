// cp
#include <dirent.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    if (argc < 3) {
        fprintf(stderr, "cp: not enough arguments\n");
        return EXIT_FAILURE;
    }
    if (argc > 3) {
        fprintf(stderr, "cp: too many arguments\n");
        return EXIT_FAILURE;
    }

    const char* source = argv[1];
    const char* dest = argv[2];

    FILE* fIn = fopen(source, "rb");
    if (fIn == NULL) {
        fprintf(stderr, "unable to open source file '%s': %s\n", source,
                strerror(errno));
        fclose(fIn);
        return EXIT_FAILURE;
    }
    FILE* fOut = fopen(dest, "wb");
    if (fOut == NULL) {
        fprintf(stderr, "unable to open dest file '%s': %s\n", dest,
                strerror(errno));
        fclose(fOut);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;
    char buf[4096];
    size_t read_bytes = 0;

    while ((read_bytes = fread(buf, 1, sizeof(buf), fIn)) != 0) {
        if (fwrite(buf, 1, sizeof(buf), fOut) != read_bytes) {
            fprintf(stderr, "cp: error occurred when copying the file");
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    // Check for errors when copying
    if (feof(fIn) == 0 && ferror(fIn) != 0) {
        fprintf(stderr, "an error occurred when copying the file\n");
        status = EXIT_FAILURE;
    }

cleanup:
    fclose(fIn);
    fclose(fOut);

    return status;
}
