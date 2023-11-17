#include "shell.h"

/**
 * main - Entry point for the setenv program.
 * Return: Always 0.
 */
/* int main(void)
{
    char *variable = "MY_VARIABLE";
    char *value = "my_value";

    if (_setenv(variable, value, 1) == 0)
    {
        printf("%s=%s added or modified successfully.\n", variable, value);
    }
    else
    {
        fprintf(stderr, "Failed to add or modify %s=%s.\n", variable, value);
    }

    return 0;
    }*/

/**
 * _setenv - Changes or adds an environment variable.
 * @name: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @overwrite: Flag to indicate whether to overwrite an existing variable.
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    if (name == NULL || value == NULL)
        return -1;

    if (overwrite || _getenv(name) == NULL)
    {
        char *env_variable = malloc(strlen(name) + strlen(value) + 2);

        if (env_variable != NULL)
        {
            sprintf(env_variable, "%s=%s", name, value);
            putenv(env_variable);
            return 0;
        }
    }

    return -1;
}
