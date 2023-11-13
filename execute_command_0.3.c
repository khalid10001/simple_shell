#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_command - Execute the given command
 * @input: Command to be executed
 */
void execute_command(char *input)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) /* Child process */
    {
        char *token;
        char *args[10]; /* Assuming a maximum of 10 arguments */
        int i = 0;

        /* Tokenize the input to get the command and arguments */
        token = strtok(input, " ");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; /* Null-terminate the argument list */

        /* Check if the command exists in the PATH */
        if (access(args[0], X_OK) == -1)
        {
            printf(":) %s: command not found\n", args[0]);
            exit(EXIT_FAILURE);
        }

        execvp(args[0], args); /* Execute the command with arguments */
        perror(args[0]); /* If execvp fails */
        exit(EXIT_FAILURE);
    }
    else /* Parent process */
    {
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
        {
            printf(":) %s: command not found\n", input);
        }
    }
}
