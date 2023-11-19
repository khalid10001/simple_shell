#include "shell.h"

/**
 * _strncpy - a function that copies up to 'n' characters from the source
 *		string to the destination.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *str = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (str);
}

/**
 * _strncat - a function that concatenates up to 'n' characters from the source
 *		string to the destination.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to concatenate.
 * Return: A pointer to the destination string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *str = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (str);
}

/**
 * _strchr - afunction that locates the first occurrence of a character
 *		in a string.
 * @s: The string to search.
 * @c: The character to locate.
 * Return: A pointer to the first occurrence of 'c' in 's' or NULL if not found
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		return (s);
	} while (*s++ != '\0');

	return (NULL);
}
