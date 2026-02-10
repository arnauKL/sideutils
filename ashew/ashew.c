// ashew: dummy shell
// WIP

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 4096

char *
ashew_read_line(void)
{
    char *buf = malloc(sizeof(char) * MAX_SIZE);
    int idx = 0;

    if (!buf) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read char by char
        char c = getchar(); // This should be an int bcs EOF is an int
                            // but when will I get EOF in a shell?
        buf[idx++] = c;

        if (idx == MAX_SIZE) {
            // Reallocate buffer
        }
    }
    return buf;
}

void
ashew_loop(void)
{
    int ok = 1;
    char *line;
    char **args; // parsed from line

    do {
        printf("ashew > ");
        fflush(stdout);
        line = ashew_read_line();
        // args = ashew_parse_args(line);
        // ok = ashew_execute(args);
    } while (ok);
}

int
main(int argc, char *argv[])
{
    // Main loop
    ashew_loop();

    // Cleanup

    return EXIT_SUCCESS;
}
