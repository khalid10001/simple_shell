#include "shell.h"
#include <stdio.h>

void compare_env_vs_environ(void);

/**
 * main - Entry point for the env_vs_environ program.
 * Return: Always 0.
 */
/*int main(void)
{
    compare_env_vs_environ();
    return 0;
    }*/

/**
 * compare_env_vs_environ - Compares the addresses of env and environ.
 */
void compare_env_vs_environ(void)
{
  extern char **environ; /* Declare environ here */ 
    char **env = environ;

    printf("Address of env: %p\n", (void *)env);
    printf("Address of environ: %p\n", (void *)environ);
    printf("Are they the same? %s\n", (environ == env) ? "Yes" : "No");
}
