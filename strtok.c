#include "shell.h"

/**
 * customStrchr - Locates the first occurrence of a character in a string.
 * @str: The string to search.
 * @c: The character to locate.
 * Return: A pointer to the located character, or NULL if not found.
 */
char *customStrchr(const char *str, int c)
{
	for (; *str != (char)c; str++)
	{
		if (!*str)
			return (NULL);
	}
	return ((char *)str);
}

/**
 * customStrspn - Computes the length of the maximum initial segment of string
 * @str: The string to compute the length.
 * @delimiters: String containing delimiting characters.
 * Return: The length of the segment.
 */
size_t customStrspn(const char *str, const char *delimiters)
{
	size_t length;

	for (length = 0; *str && customStrchr(delimiters, *str++); length++)
		;

	return (length);
}

/**
 * customStrcspn - Computes the length of the maximum initial segment of string
 * @str: The string to check.
 * @delimiters: String containing delimiting characters.
 * Return: The length of the segment.
 */
size_t customStrcspn(const char *str, const char *delimiters)
{
	size_t length;

	for (length = 0; *str; str++, length++)
	{
		if (customStrchr(delimiters, *str))
			return (length);
	}

	return (length);
}

/**
 * customStrtok - Breaks the string into tokens and null-terminates them.
 * @str: The string to tokenize.
 * @delimiters: String with the characters that delimit the string.
 * Return: The first/next token if possible, a null-pointer otherwise.
 */
char *customStrtok(char *str, const char *delimiters)
{
	static char *p;

	if (str)
		p = str;
	else if (!p)
		return (NULL);

	str = p + customStrspn(p, delimiters);
	p = str + customStrcspn(str, delimiters);

	if (p == str)
		return (p = NULL);

	p = *p ? *p = 0, p + 1 : 0;
	return (str);
}
