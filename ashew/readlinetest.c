#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    char *line; // readline mallocs for me.

    while ((line = readline("test > ")) != NULL) {

        printf("I got: %s\n", line);

        free(line);
    }

    printf("\n");

    return 0;
}
