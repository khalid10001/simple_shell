#include "shell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void display_prompt(void);
char *get_input(char *input);
int execute_command(const char *command);

/**
 * main - Entry point for the simple_shell program.
 * Return: Always 0.
 */
int main(void)
{
    char input[MAX_INPUT_SIZE];

    while (1)
    {
        display_prompt();

        if (get_input(input) == NULL)
        {
            printf("\n");
            break; /* EOF (Ctrl+D) detected */
        }

        if (execute_command(input) == -1)
            fprintf(stderr, "Error executing command: %s\n", input);
    }

    return EXIT_SUCCESS;
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
    printf("#cisfun$ ");
}

/**
 * get_input - Get input from the user
 * @input: Buffer to store the input
 * Return: Pointer to the input buffer
 */
char *get_input(char *input)
{
    size_t len;

    printf("$ ");
    if (getline(&input, &len, stdin) == -1)
    {
        if (feof(stdin))
            exit(EXIT_SUCCESS);
        perror("getline");
        exit(EXIT_FAILURE);
    }

    return input;
}

/**
 * execute_command - Executes a command entered by the user.
 * @command: The command to execute.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(const char *command)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        return -1;
    }

    if (child_pid == 0) /* Child process */
    {
	/* Split the command string into tokens */
        char **args = (char **)malloc(2 * sizeof(char *));
        if (args == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        args[0] = (char *)command;
        args[1] = NULL;

        if (execvp(command, args) == -1)
        {
            perror(command);
            exit(EXIT_FAILURE);
        }
    }
    else /* Parent process */
    {
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
            fprintf(stderr, "%s: command not found\n", command);
    }

    return 0;
}
