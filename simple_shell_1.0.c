#include "main.h"

#define MAX_INPUT_SIZE 1024

/**
 * main - Simple Shell
 * Return: Always 0.
 */
int main(void)
{
    char input[MAX_INPUT_SIZE];

    while (1)
    {
        printf("$ ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            break; /* EOF (Ctrl+D) detected */
        }

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0'; /* remove newline */
        }

        if (strcmp(input, "env") == 0)
        {
            env_shell();
            continue;
        }

        if (strcmp(input, "exit") == 0)
        {
            exit_shell();
            break;
        }

        int status = execute_command(input);

        if (status == 127)
        {
            printf("%s: command not found\n", input);
        }
    }

    return EXIT_SUCCESS;
}

/**
 * env_shell - Print the current environment
 */
void env_shell(void)
{
    extern char **environ;  // Declaration of the 'environ' variable
    int i = 0;

    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
}

/**
 * exit_shell - Exits the shell
 */
void exit_shell(void)
{
    exit(EXIT_SUCCESS);
}

/**
 * execute_command - Execute the given command
 * @command: The command to execute
 * Return: Exit status of the command
 */
int execute_command(char *command)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) /* Child process */
    {
        execlp(command, command, (char *)NULL); /* Execute the command */
        perror(command); /* If execlp fails */
        exit(EXIT_FAILURE);
    }
    else /* Parent process */
    {
        int status;
        waitpid(child_pid, &status, 0);

        return status;
    }
}
