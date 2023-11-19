#include "shell.h"

/**
 * _eputs - a function that prints a string to the standard error stream.
 * @str: The string to be printed to the standard error stream.
 */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - a function that prints a character to the standard error stream
 *		or flushes the buffer.
 * @c: The character to be printed or BUF_FLUSH to flush the buffer.
 * Return: 1 if successful, 0 otherwise.
 */
int _eputchar(char c)
{
	static int k;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buffer, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buffer[k++] = c;
	return (1);
}

/**
 * _putfd - a function that prints a character to the specified
 *		file descriptor or flushes the buffer.
 * @c: The character to be printed or BUF_FLUSH to flush the buffer.
 * @fd: The file descriptor to which the character or buffer should be written.
 * Return: 1 if successful, 0 otherwise.
 */
int _putfd(char c, int fd)
{
	static int k;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buffer[k++] = c;
	return (1);
}

/**
 * _putsfd - a function that prints a string to the specified file descriptor.
 * @str: The string to be printed to the specified file descriptor.
 * @fd: The file descriptor to which the string should be written.
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
	{
		k += _putfd(*str++, fd);
	}
	return (k);
}
