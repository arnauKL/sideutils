#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PROGRAM_NAME        "wc"
#define BUFFER_SIZE         4096
#define DEBUG_PRINT_INT(x)  printf("%s: %d\n", #x, (x))
#define DEBUG_PRINT_CHAR(x) printf("%s: %c\n", #x, (x))

struct file_statistics
{
    uint64_t n_lines;
    uint64_t n_words;
    uint64_t n_bytes;
};

/* wc normal behaviour:
    $ wc cp.c
    62  182 1527 cp.c
    $ wc -l cp.c # -l: lines
    62 cp.c
    $ wc -c cp.c # -c: bytes
    1527 cp.c
    $ wc -m cp.c # -m: chars
    1527 cp.c
    $ wc -w cp.c # -w: words
    182 cp.c
 */

int count(int fildes, struct file_statistics *fs);
void update_totals(struct file_statistics *totals, struct file_statistics *current);
void print_stats(struct file_statistics *fs, const char *filename);

int
main(int argc, char *argv[])
{
    int file_descriptor;

    struct file_statistics cummulative_stats = {0};
    struct file_statistics file_stats = {0};

    int exit_status = EXIT_SUCCESS;

    if (argc < 2) {
        // Read from stdin if no file is given
        file_descriptor = STDIN_FILENO;
        int tmp = count(file_descriptor, &file_stats);

        if (tmp < 0) {
            fprintf(stderr, "%s: %s\n", PROGRAM_NAME, strerror(errno));
            exit_status = EXIT_FAILURE;
        }

        print_stats(&file_stats, "");

    } else {
        for (int i = 1; i < argc; i++) {

            file_descriptor = open(argv[i], O_RDONLY);

            if (file_descriptor < 0) {
                fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, argv[i], strerror(errno));
                exit_status = EXIT_FAILURE;
                continue;
            }

            int tmp = count(file_descriptor, &file_stats);

            // the real counting
            if (tmp < 0) {
                fprintf(stderr, "%s: %s\n", PROGRAM_NAME, strerror(errno));
                exit_status = EXIT_FAILURE;
                close(file_descriptor);
                continue;
            }

            close(file_descriptor);

            print_stats(&file_stats, argv[i]);
            update_totals(&cummulative_stats, &file_stats);

            file_stats = (struct file_statistics){0};
        }

        if (argc > 2) print_stats(&cummulative_stats, "total");
    }

    return exit_status;
}

int
count(int fildes, struct file_statistics *fs)
{
    unsigned char buffer[BUFFER_SIZE];

    int bytes_read = 0;
    errno = 0;
    bool inside_word = false;

    while ((bytes_read = read(fildes, buffer, sizeof(buffer))) > 0) {
        fs->n_bytes += bytes_read;

        for (int i = 0; i < bytes_read; i++) {

            if (buffer[i] == '\n') fs->n_lines++;

            if (inside_word && isspace(buffer[i])) {
                inside_word = false;
            } else if (!inside_word && !isspace(buffer[i])) {
                fs->n_words++;
                inside_word = true;
            }
        }
    }

    return bytes_read < 0 ? -1 : 0;
}

inline void
update_totals(struct file_statistics *totals, struct file_statistics *current)
{
    totals->n_bytes += current->n_bytes;
    totals->n_words += current->n_words;
    totals->n_lines += current->n_lines;
}

inline void
print_stats(struct file_statistics *fs, const char *filename)
{
    // ld might not match uint64_t
    printf(" %4ld %4ld %4ld %s\n", fs->n_lines, fs->n_words, fs->n_bytes, filename);
}
