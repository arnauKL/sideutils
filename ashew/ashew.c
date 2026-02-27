// ashew: dummy shell
// WIP

// clang-format off
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
// clang-format on

#define PROGRAM_NAME "ashew"
#define ASHEW_PROMPT "ashew > "

#define HISTORY_FILE ".ashew_history"
#define HISTORY_SIZE 10 // ridiculous

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

int
main(void)
{
    ashew_loop();
    return EXIT_SUCCESS;
}

int
ashew_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "%s: expected argument to \"cd\"\n", PROGRAM_NAME);
        return 1;
    }

    if (chdir(args[1]) != 0) {
        fprintf(stderr, "%s: %s", PROGRAM_NAME, strerror(errno));
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
#ifdef HISTORY_FILE
    read_history(HISTORY_FILE); // readline lib does history for me
#endif

    using_history(); // readline lib does history for me
    stifle_history(HISTORY_SIZE);

    int ok = 1;
    char *line;  // gets malloc-ed by readline
    char **args; // parsed from line

    while (ok && (line = readline(ASHEW_PROMPT)) != NULL) {
        add_history(line);

        args = split_line(line);
        ok = execute(args);

        free(line);
        free(args);
    }

#ifdef HISTORY_FILE
    write_history(HISTORY_FILE);
#endif

    clear_history();
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
            fprintf(stderr, "%s: %s\n", args[0], strerror(errno));
            exit(EXIT_FAILURE); // If it returns, always kill the child process
        }
    } else if (pid < 0) {
        fprintf(stderr, "%s: %s\n", PROGRAM_NAME, strerror(errno));
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
        fprintf(stderr, "%s: allocation error\n", PROGRAM_NAME);
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
                fprintf(stderr, "%s: reallocation error\n", PROGRAM_NAME);
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
