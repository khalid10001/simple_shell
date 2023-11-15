#include "shell.h"

/**
 * main - Entry point for the env_vs_environ program.
 * Return: Always 0.
 */
int main(void)
{
    compare_env_vs_environ();
    return 0;
}

/**
 * compare_env_vs_environ - Compares the addresses of env and environ.
 */
void compare_env_vs_environ(void)
{
    extern char **environ;

    printf("Address of env: %p\n", environ);
    printf("Address of environ: %p\n", environ);
    printf("Are they the same? %s\n", (environ == env) ? "Yes" : "No");
    printf("Note: This may or may not make sense depending on the system.\n");
}
