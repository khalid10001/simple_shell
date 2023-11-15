#include "shell.h"

/**
 * main - Entry point for the unsetenv program.
 * Return: Always 0.
 */
/* int main(void)
{
    char *variable = "MY_VARIABLE";

    if (_unsetenv(variable) == 0)
    {
        printf("%s unset successfully.\n", variable);
    }
    else
    {
        fprintf(stderr, "Failed to unset %s.\n", variable);
    }

    return 0;
    }*/ 

/**
 * _unsetenv - Deletes the variable name from the environment.
 * @name: Name of the environment variable to delete.
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
    if (name == NULL)
        return -1;

    if (getenv(name) != NULL)
    {
        char *env_variable = malloc(strlen(name) + 2);

        if (env_variable != NULL)
        {
            sprintf(env_variable, "%s=", name);
            putenv(env_variable);
            return 0;
        }
    }

    return -1;
}
