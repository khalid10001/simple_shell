#include "shell.h"

/**
 * tokenizeString - Tokenize a string into an array of tokens.
 * @userInput: User command string.
 * Return: Pointer to an array of tokens.
 */
char **tokenizeString(char *userInput)
{
	char **userCommand = NULL;
	char *token = NULL;
	size_t i = 0;
	int tokenCount = 0;

	/* Return NULL if the input string is empty */
	if (userInput == NULL)
		return (NULL);

	/* Count the number of tokens (words) in the input string */
	while (userInput[i])
	{
		if (userInput[i] == ' ')
		{
			while (userInput[i] == ' ') /* Skip consecutive spaces */
			i++;
			continue;
		}
		tokenCount++;
		i++;
	}
	/* Return NULL if the input consists only of spaces */
	if (tokenCount == 0)
		return (NULL);
	/* Allocate memory for the array of tokens */
	userCommand = malloc(sizeof(char *) * (tokenCount + 1));
	if (userCommand == NULL)
		return (NULL);
	/* Tokenize the input string using customStrtok */
	token = customStrtok(userInput, " \n\t\r");
	i = 0;
	while (token != NULL)
	{
	userCommand[i] = token;
	token = customStrtok(NULL, " \n\t\r");
	i++;
	}
	/* Set the last element of the array to NULL to indicate the end */
	userCommand[i] = NULL;
	return (userCommand);
}
