// ls
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ls(const char* path) {
    // List files in path
    DIR* d = opendir(path);
    if (d == NULL) {
        fprintf(stderr, "ls: unable to open directory: '%s\n", strerror(errno));
        return;
    }

    struct dirent* ent;
    errno = 0;
    while ((ent = readdir(d)) != NULL) {
        // does not print in order but works
        printf("%s\n", ent->d_name);
    }

    if (errno != 0) {
        fprintf(stderr, "ls: unable to read directory: %s\n", strerror(errno));
    }

    closedir(d);
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        ls(".");
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        ls(argv[i]);
    }

    return 0;
}
