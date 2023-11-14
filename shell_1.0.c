#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Simple Shell 1.0
 * Return: Always 0.
 */
int main(void)
{
    char input[MAX_INPUT_SIZE];

    while (1)
    {
        printf(":) ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            exit_shell(); /* EOF (Ctrl+D) detected, exit the shell */
        }

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0'; /* remove newline */
        }

        execute_command(input);
    }

    return EXIT_SUCCESS;
}
