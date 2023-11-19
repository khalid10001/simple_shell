#include "shell.h"

/**
 * strtow - a function that splits a string into an array of strings based
 *		on a set of delimiter characters.
 * @str: The input string to be split.
 * @d: The delimiter characters used for splitting.
 * Return: An array of strings, or NULL if the input is invalid
 *	or if memory allocation fails.
 */
char **strtow(char *str, char *d)
{
	int a, b, x, z, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) &&
			(is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(str[a], d))
			a++;
		x = 0;
		while (!is_delim(str[a + x], d) && str[a + x])
			x++;
		s[b] = malloc((x + 1) * sizeof(char));
		if (!s[b])
		{
			for (x = 0; x < b; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < x; z++)
			s[b][z] = str[a++];
		s[b][z] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * strtow2 - a function that splits a string into an array of strings based on
 *		a single delimiter character.
 * @str: The input string to be split.
 * @d: The single delimiter character used for splitting.
 * Return: An array of strings, or NULL if the input is invalid
 *	or if memory allocation fails.
 */
char **strtow2(char *str, char d)
{
	int a, b, x, z, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
			(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		x = 0;
		while (str[a + x] != d && str[a + x] && str[a + x] != d)
			x++;
		s[b] = malloc((x + 1) * sizeof(char));
		if (!s[b])
		{
			for (x = 0; x < b; x++)
			free(s[x]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < x; z++)
			s[b][z] = str[a++];
		s[b][z] = 0;
	}
	s[b] = NULL;
	return (s);
}
