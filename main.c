#include "shell.h"

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
 * get_input - Reads a line of input from the user.
 * @input: Buffer to store the input.
 * Return: Pointer to the input buffer.
 */
char *get_input(char *input)
{
    if (fgets(input, sizeof(input), stdin) == NULL)
        return NULL;

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0'; /* remove newline */

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
        if (execvp(command, NULL) == -1)
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
