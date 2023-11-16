#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void display_prompt(void)
{
    printf("#cisfun$ ");
}

char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);

    if (read == -1)
    {
        if (feof(stdin))
            return NULL;

        perror("getline");
        exit(EXIT_FAILURE);
    }

    /* Remove newline character */
    if (line[read - 1] == '\n')
        line[read - 1] = '\0';

    return line;
}

void execute_command(char *command)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        /* Child process */
        if (execlp(command, command, (char *)NULL) == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        wait(NULL);
    }
}
