#include "shell.h"

int _cd(const char *directory);

/**
 * main - Entry point for the cd_builtin program.
 * Return: Always 0.
 */
/* int main(void)
{
    char *directory = "/path/to/directory";

    if (_cd(directory) == 0)
    {
        printf("Changed to %s\n", directory);
    }
    else
    {
        fprintf(stderr, "Failed to change to %s\n", directory);
    }

    return 0;
    }*/

/**
 * _cd - Changes the current directory of the process.
 * @directory: Directory to change to. If NULL, changes to $HOME.
 * Return: 0 on success, -1 on failure.
 */
int _cd(const char *directory)
{
    const char *new_directory;

    if (directory == NULL)
    {
        new_directory = getenv("HOME");

        if (new_directory == NULL)
            return -1;
    }
    else
    {
        new_directory = directory;
    }

    if (chdir(new_directory) != 0)
    {
        perror("chdir");
        return -1;
    }

    /* Update the environment variable PWD */
    setenv("PWD", new_directory, 1);

    return 0;
}
