// ashew: dummy shell
// WIP

#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_LINE_BUFFER_SIZE 256

#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITER                                                                            \
    " \t\r\n\a" // very limited, should be expanded. Ignores
                // quotes, escaping sequences, etc.
#define REDIRECT_OPERATOR '>'

void ashew_loop(void);
int execute(char **args);
int launch(char **args);
char **split_line(char *line);
// Builtins:
int ashew_cd(char **args);
int ashew_exit(char **args);
int ashew_help(char **args);

char *builtin_str[] = {"cd", "help", "exit"};

int (*builtin_func[])(char **) = {&ashew_cd, &ashew_help, &ashew_exit};

int
ashew_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

// ----------------- function implementations -----------------

int
// main(int argc, char *argv[])
main(void)
{
    ashew_loop();
    return EXIT_SUCCESS;
}

int
ashew_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "ashew: expected argument to \"cd\"\n");
        return 1;
    }

    if (chdir(args[1]) != 0) {
        fprintf(stderr, "ashew: %s", strerror(errno));
    }

    return 1;
}

int
ashew_exit(char **args)
{
    // args are not used but this simplifies calling the function ptr
    return 0;
}

int
ashew_help(char **args)
{
    // Following ash's help

    fprintf(stdout, "Built-in commands: \n");
    fprintf(stdout, "------------------ \n");
    for (int i = 0; i < ashew_num_builtins(); i++) {
        fprintf(stdout, "%s ", builtin_str[i]);
    }
    fprintf(stdout, "\n");
    return 1;
}

/* Basic loop of a shell:
Read: Read the command from standard input.
Parse: Separate the command string into a program and arguments.
Execute: Run the parsed command. */
void
ashew_loop(void)
{
    int ok = 1;
    char *line;  // gets malloc-ed by readline
    char **args; // parsed from line

    while (ok && (line = readline("ashew > ")) != NULL) {
        args = split_line(line);
        ok = execute(args);

        free(line);
        free(args);
    }
}

int
execute(char **args)
{
    if (args == NULL || args[0] == NULL) { // Sweet short-circuit saves the day
        // An empty command was entered.
        return 1;
    }

    for (int i = 0; i < ashew_num_builtins(); i++) {
        // Check if it's any of our builtins
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return launch(args);
}

int
launch(char **args)
{
    pid_t pid, wpid; /* I should be using wpid for sth */
    int status;

    pid = fork();
    // Now we have 2 threads:

    if (pid == 0) {
        // Child process
        // execvp does the execution of the arguments
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "ashew: %s: %s\n", args[0], strerror(errno));
            exit(EXIT_FAILURE); // If it returns, always kill the child process
        }
    } else if (pid < 0) {
        fprintf(stderr, "ashew: %s\n", strerror(errno));
    } else {
        // Parent thread, wait for child to end
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

char **
split_line(char *line)
{
    int buffer_size = TOKEN_BUFFER_SIZE;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token = NULL;
    int idx = 0;

    if (!tokens) {
        fprintf(stderr, "ashew: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIMITER);

    while (token != NULL) {

        if (token[0] == REDIRECT_OPERATOR) {
            // Redirection
        }

        tokens[idx++] = token;

        if (idx >= buffer_size - 1) { // Leave room for the last NULL
            // Reallocate
            buffer_size += TOKEN_BUFFER_SIZE;
            char **tmp_tokens = realloc(tokens, buffer_size * sizeof(char *));
            if (!tmp_tokens) {
                fprintf(stderr, "ashew: reallocation error\n");
                // Free original memory and return
                free(tokens);
                return NULL;
            }

            tokens = tmp_tokens;
        }

        // strtok has state, stores the next char after the split token:
        token = strtok(NULL, TOKEN_DELIMITER); // That's why NULL is passed
    }

    tokens[idx] = NULL;
    return tokens;
}
