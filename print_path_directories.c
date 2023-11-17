#include "shell.h"

/**
 * main - Entry point for the print_path_directories program.
 * Return: Always 0.
 */
/* int main(void)
{
    printf("Directories in PATH:\n");
    print_path_directories();
    return 0;
    }*/ 

/**
 * print_path_directories - Prints each directory in the PATH environment variable.
 */
void print_path_directories(void)
{
    char *path_variable = "PATH";
    char *path_value = _getenv(path_variable);

    if (path_value != NULL)
    {
        char *directory = strtok(path_value, ":");

        while (directory != NULL)
        {
            printf("%s\n", directory);
            directory = strtok(NULL, ":");
        }
    }
    else
    {
        printf("PATH variable not found.\n");
    }
}
