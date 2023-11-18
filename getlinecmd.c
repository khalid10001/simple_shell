#include "shell.h"

/**
 * getCommandInput - Prompt the user with "$ " and wait for input.
 * Return: The line of string input from the user.
 */
/*char *getCommandInput(void)
{
	char *inputLine = NULL;
	size_t bufferSize = 0;

	 Print the shell prompt if STDIN is a terminal 
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	 Read the input line from the user 
	if (getline(&inputLine, &bufferSize, stdin) == -1)
	{
		free(inputLine);
		return (NULL);
	}

	return (inputLine);
}*/
char *getCommandInput(void)
{
    char *inputLine = NULL;
    size_t bufferSize = 0;
    ssize_t bytesRead;

    /* Print the shell prompt if STDIN is a terminal */
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "$ ", 2);

    /* Read the input line from the user */
    bytesRead = getline(&inputLine, &bufferSize, stdin);

    if (bytesRead == -1)
    {
        perror("getline error");
        free(inputLine);  /* Only free if inputLine is not NULL*/
        return NULL;
    }

    return inputLine;
}

