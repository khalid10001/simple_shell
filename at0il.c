#include "shell.h"

/**
 * interactive - This function that Checks if the program is running
 *		in an interactive mode.
 * @info: A pointer to a structure containing information about the program.
 * Return: 1 if running interactively, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - a function that checks if a character is a delimiter.
 * @c: The character to be checked.
 * @delim: A string containing delimiter characters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - a function checks if a character is an alphabetic character.
 * @c: The character to be checked.
 * Return: 1 if the character is an alphabetic character, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - a function that Converts a string to an integer.
 * @s: The string to be converted to an integer.
 * Return: The converted integer value.
 */
int _atoi(char *s)
{
	int x, sign = 1, flag = 0, op;
	unsigned int res = 0;

	for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
	if (s[x] == '-')
		sign *= -1;

	if (s[x] >= '0' && s[x] <= '9')
	{
		flag = 1;
		res *= 10;
		res += (s[x] - '0');
	}
	else if (flag == 1)
		flag = 2;
	}

	if (sign == -1)
		op = -res;
	else
		op = res;

	return (op);
}
