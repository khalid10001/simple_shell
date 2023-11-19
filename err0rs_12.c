#include "shell.h"

/**
 * _erratoi - a function that converts a string to an integer.
 * @s: The string to be converted to an integer.
 * Return: The converted integer value, or -1 if an error occurs.
 */
int _erratoi(char *s)
{
	int k = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* Skip leading plus sign. */
	for (k = 0; s[k] != '\0'; k++)
	{
		if (s[k] >= '0' && s[k] <= '9')
		{
			res *= 10;
			res += (s[k] - '0');
			if (res > INT_MAX)
			return (-1);  /* Integer out of range. */
		}
		else
			return (-1);  /* Invalid character found. */
	}
	return (res);
}

/**
 * print_error - a function that prints an error message to the standard
 *		error stream.
 * @info: A pointer to a structure containing information about the program.
 * @estr: The error message to be printed.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - a function that prints an integer to the specified file descriptor
 * @input: The integer to be printed.
 * @fd: The file descriptor to which the integer should be written.
 * Return: The number of characters written.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, i = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		i++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + curr / x);
			i++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	i++;

	return (i);
}

/**
 * convert_number - a function that converts a number to a string with
 *	specified base and flags.
 * @num: The number to be converted.
 * @base: The base to use for the conversion.
 * @flags: Flags for the conversion.
 * Return: A pointer to the converted string.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *ar;
	static char buf[50];
	char sign = 0;
	char *p;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		sign = '-';
	}
	ar = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do {
		*--p = ar[number % base];
		number /= base;
	} while (number != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * remove_comments - a function that removes comments from a string.
 * @buf: The string from which comments should be removed.
 */
void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
	{
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
	}
}
