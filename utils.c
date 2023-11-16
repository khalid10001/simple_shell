#include "shell.h"

/**
 * concatenateStrings - Concatenate two strings.
 * @destination: Destination string.
 * @source: Source string.
 * Return: Pointer to the destination string.
 */
char *concatenateStrings(char *destination, char *source)
{
	int destIndex;
	int sourceIndex = 0;

	for (destIndex = 0; destination[destIndex] != '\0'; destIndex++)
		;

	for (sourceIndex = 0; source[sourceIndex] != '\0'; destIndex++, sourceIndex++)
	{
		destination[destIndex] = source[sourceIndex];
	}

	destination[destIndex] = '\0';
	return (destination);
}

/**
 * compareStrings - Compare the values of two strings.
 * @string1: First string.
 * @string2: Second string.
 * Return: The difference between the first differing characters.
 */
int compareStrings(char *string1, char *string2)
{
	int index = 0;

	while (string1[index] != '\0' && string2[index] != '\0')
	{
		if (string1[index] != string2[index])
			return ((int)(string1[index] - string2[index]));
		index++;
	}

	return (0);
}

/**
 * getStringLength - Get the length of a string.
 * @string: A pointer to the string.
 * Return: The length of the string.
 */
int getStringLength(char *string)
{
	int length;

	for (length = 0; *(string + length) != '\0'; length++)
	{
		length++;
	}

	return (length);
}

/**
 * compareStringsN - Compare the values of two strings up to n characters.
 * @string1: First string.
 * @string2: Second string.
 * @n: Number of characters to compare.
 * Return: The difference between the first differing characters.
 */
size_t compareStringsN(char *string1, char *string2, size_t n)
{
	size_t index = 0, difference;

	while (string1[index] != '\0' && index < n)
	{
		difference = string1[index] - string2[index];

		if (difference != 0)
		{
			return (difference);
		}
		index++;
	}

	return (0);
}

/**
 * copyString - Copy the source string to the destination string.
 * @destination: Destination of the copy.
 * @source: Source of the copy.
 * Return: Pointer to the destination string.
 */
char *copyString(char *destination, char *source)
{
	int i;

	for (i = 0; *(source + i) != '\0'; ++i)
	{
		*(destination + i) = *(source + i);
	}

	*(destination + i) = *(source + i);

	return (destination);
}
