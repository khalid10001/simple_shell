#include "main.h"
#include <stdio.h>

extern char **environ;  // Declaration of the 'environ' variable

/**
 * env_shell - Print the current environment
 */
void env_shell(void)
{
    char **env = environ;

    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}
