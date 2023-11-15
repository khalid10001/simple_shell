#include "shell.h"
#include <unistd.h>

/**
 * environ_size - Calculate the size of the environ variable
 *
 * Return: Size of the environ variable
 */
size_t environ_size(void)
{
    size_t count = 0;

    while (environ && environ[count] != NULL)
        count++;

    return count;
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * @name: Name of the environment variable
 * @value: Value of the environment variable
 * @overwrite: Flag to indicate whether to overwrite an existing variable
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    size_t i, name_len = strlen(name);
    char **new_environ = NULL;
    size_t size = environ_size();

    for (i = 0; environ && environ[i] != NULL; i++)
    {
        if (strncmp(name, environ[i], name_len) == 0 && environ[i][name_len] == '=')
        {
            if (!overwrite)
                return 0;
            free(environ[i]);
            environ[i] = NULL;
            break;
        }
    }

    new_environ = malloc((size + 2) * sizeof(char *));
    if (!new_environ)
        return -1;

    for (i = 0; environ && environ[i] != NULL; i++)
        new_environ[i] = environ[i];

    new_environ[i] = malloc(name_len + strlen(value) + 2);
    if (!new_environ[i])
    {
        free(new_environ);
        return -1;
    }

    snprintf(new_environ[i], name_len + strlen(value) + 2, "%s=%s", name, value);
    new_environ[i + 1] = NULL;

    environ = new_environ;
    return 0;
}

/**
 * _unsetenv - Remove an environment variable
 * @name: Name of the environment variable
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
    size_t i, name_len = strlen(name);
    char **new_env = NULL;
    size_t size = environ_size();

    for (i = 0; environ && environ[i] != NULL; i++)
    {
        if (strncmp(name, environ[i], name_len) == 0 && environ[i][name_len] == '=')
        {
            free(environ[i]);
            environ[i] = NULL;
            break;
        }
    }

    new_env = malloc((size + 1) * sizeof(char *));
    if (!new_env)
        return -1;

    for (i = 0; environ && environ[i] != NULL; i++)
    {
        if (environ[i] != NULL)
            new_env[i] = environ[i];
    }

    new_env[i] = NULL;

    environ = new_env;
    return 0;
}
