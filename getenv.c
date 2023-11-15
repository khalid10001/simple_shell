#include "shell.h"

/**
 * main - Entry point for the getenv program.
 * Return: Always 0.
 */
/* int main(void)
{
    char *variable_name = "HOME";
    char *value;

    value = _getenv(variable_name);

    if (value)
        printf("Value of %s: %s\n", variable_name, value);
    else
        printf("Variable %s not found.\n", variable_name);

    return 0;
    }*/

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable.
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
    extern char **environ;
    int i = 0;
    char *env_var;

    while (environ[i] != NULL)
    {
        env_var = strtok(environ[i], "=");

        if (strcmp(env_var, name) == 0)
            return strtok(NULL, "=");

        i++;
    }

    return NULL;
}
