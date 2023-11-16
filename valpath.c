#include "shell.h"

/**
 * findExecutablePath - Search for the executable path in the PATH environment.
 * @command: Command input from the user.
 * @environment: Environment variables.
 * Return: 0 on success, -1 on failure.
 */
int findExecutablePath(char **command, char **environment)
{
	char *token = NULL, *relativePath = NULL, *absolutePath = NULL;
	size_t commandLength, tokenLength;
	struct stat statResult;
	(void) environment;

	/* Check if the command is an absolute path 
	if (stat(*command, &statResult) == 0)
		return (-1);*/
	/* Get the PATH variable from the environment 
	relativePath = getPath(environment);
	if (!relativePath)
		return (-1);*/
	/* Tokenize the PATH variable and search for the executable */
	for (token = customStrtok(relativePath, ":"),
			commandLength = getStringLength(*command);
			token;
			token = customStrtok(NULL, ":"))
	{
		tokenLength = getStringLength(token);
		absolutePath = malloc(sizeof(char) *
				(tokenLength + commandLength + 2));
		if (!absolutePath)
		{
			free(relativePath);
			return (-1);
		}
		/*absolutePath = copyString(absolutePath, token);
		concatenateStrings(absolutePath, "/");
		concatenateStrings(absolutePath, *command);*/
		if (stat(absolutePath, &statResult) == 0)
		{
			*command = absolutePath;
			free(relativePath);
			return (0);
		}
		free(absolutePath);
	}
	free(relativePath);
	return (-1);
}
