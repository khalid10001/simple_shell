#include "shell.h"

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

/**
 * env_vs_environ - Prints the address of env and environ.
 */
void env_vs_environ(void)
{
    extern char **environ;
    char **env = environ;

    printf("Address of env: %p\n", (void *)env);
    printf("Address of environ: %p\n", (void *)environ);
}

/**
 * _getenv - Gets an environment variable.
 * @name: The name of the environment variable.
 * Return: The value of the environment variable or NULL if not found.
 */
char *_getenv(const char *name)
{
    extern char **environ;

    while (*environ)
    {
        if (strncmp(*environ, name, strlen(name)) == 0 && (*environ)[strlen(name)] == '=')
            return (*environ + strlen(name) + 1);

        environ++;
    }

    return NULL;
}

/**
 * print_path_directories - Prints each directory in the PATH environment variable.
 */
void print_path_directories(void)
{
    char *path = _getenv("PATH");

    if (path != NULL)
    {
        char *token = strtok(path, ":");

        while (token != NULL)
        {
            printf("%s\n", token);
            token = strtok(NULL, ":");
        }
    }
}

/**
 * build_path_linked_list - Builds a linked list of the PATH directories.
 * Return: A pointer to the head of the linked list.
 */
PathNode *build_path_linked_list(void)
{
    PathNode *head = NULL;
    char *path = _getenv("PATH");

    if (path != NULL)
    {
        char *token = strtok(path, ":");

        while (token != NULL)
        {
            PathNode *new_node = malloc(sizeof(PathNode));
            if (new_node == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            new_node->directory = strdup(token);
            new_node->next = head;
            head = new_node;

            token = strtok(NULL, ":");
        }
    }

    return head;
}

/**
 * _setenv - Changes or adds an environment variable.
 * @name: The name of the environment variable.
 * @value: The value to set.
 * @overwrite: If non-zero, overwrite the variable if it already exists.
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    extern char **environ;

    if (name == NULL || value == NULL)
        return -1;

    size_t name_len = strlen(name);
    size_t value_len = strlen(value);

    char **env = environ;

    while (*env)
    {
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
        {
            if (overwrite)
            {
                free(*env);
                *env = malloc(name_len + value_len + 2);
                if (*env == NULL)
                {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                snprintf(*env, name_len + value_len + 2, "%s=%s", name, value);
                return 0;
            }
            else
            {
                return 0;
            }
        }

        env++;
    }

    if (overwrite || getenv(name) == NULL)
    {
        char **new_environ = malloc((environ_size() + 2) * sizeof(char *));
        if (new_environ == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        env = environ;
        char **new_env = new_environ;

        while (*env)
        {
            *new_env = strdup(*env);
            if (*new_env == NULL)
            {
                perror("strdup");
                exit(EXIT_FAILURE);
            }
            env++;
            new_env++;
        }

        *new_env = malloc(name_len + value_len + 2);
        if (*new_env == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        snprintf(*new_env, name_len + value_len + 2, "%s=%s", name, value);

        *++new_env = NULL;

        environ = new_environ;

        return 0;
    }

    return -1;
}

/**
 * _unsetenv - Deletes the variable name from the environment.
 * @name: The name of the environment variable to delete.
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
    extern char **environ;

    if (name == NULL)
        return -1;

    size_t name_len = strlen(name);

    char **env = environ;
    char **new_environ = malloc((environ_size() + 1) * sizeof(char *));
    if (new_environ == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char **new_env = new_environ;

    while (*env)
    {
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
        {
            env++;
            continue;
        }

        *new_env = strdup(*env);
        if (*new_env == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        env++;
        new_env++;
    }

    *new_env = NULL;

    environ = new_environ;

    return 0;
}

int environ_size(void)
{
    extern char **environ;
    char **env = environ;
    int size = 0;

    while (*env)
    {
        size++;
        env++;
    }

    return size;
}
