#include "shell.h"

/**
 * main - Entry point for the printenv program.
 * Return: Always 0.
 */
int main(void)
{
    print_env();
    return 0;
}

/**
 * print_env - Prints the environment using the global variable environ.
 */
void print_env(void)
{
    extern char **environ;

    while (*environ)
    {
        printf("%s\n", *environ);
        environ++;
    }
}
