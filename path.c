#include "shell.h"

/**
 * getPath - Retrieve the value of the PATH variable from the environment.
 * @environment: Local environment variables.
 * Return: The value of the PATH variable.
 */
char *getPath(char **environment)
{
	size_t index = 0, var = 0, count = 5;
	char *path = NULL;

	/* Find the index of the PATH variable in the environment */
	while (compareStringsN(environment[index], "PATH=", 5))
		index++;
	/* Return NULL if PATH variable is not found */
	if (environment[index] == NULL)
		return (NULL);
	/* Calculate the length of the PATH value */
	while (environment[index][var])
	{
		var++;
		count++;
	}
	/* Allocate memory for the PATH value */
	path = malloc(sizeof(char) * (count + 1));

	/* Return NULL if memory allocation fails */
	if (path == NULL)
		return (NULL);
	/* Copy the PATH value to the allocated memory */
	var = 5;
	count = 0;
	while (environment[index][var])
	{
		path[count] = environment[index][var];
		var++;
		count++;
	}
	path[count] = '\0';
	return (path);
}
