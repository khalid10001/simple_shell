#include "shell.h"

/**
 * input_buf - a function that reads input from the standard input and updates
 *		the buffer.
 * @info: A pointer to a structure containing information about the program.
 * @buf: A pointer to the buffer where input is stored.
 * @len: A pointer to the size of the buffer.
 * Return: The number of characters read, or -1 if end-of-file is encountered.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t z = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/* bfree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		z = getline(buf, &len_p, stdin);
#else
		z = _getline(info, buf, &len_p);
#endif
		if (z > 0)
		{
			if ((*buf)[z - 1] == '\n')
			{
				(*buf)[z - 1] = '\0';
				z--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = z;
				info->cmd_buf = buf;
			}
		}
	}
	return (z);
}

/**
 * get_input - a function that processes input, handles command chaining,
 *		and updates the buffer.
 * @info: A pointer to a structure containing information about the program.
 * Return: The number of characters read, or -1 if end-of-file is encountered.
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t x, y, length;
	ssize_t z = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	z = input_buf(info, &buffer, &length);
	if (z == -1)
		return (-1);
	if (length)
	{
		y = x;
		p = buffer + x;

		check_chain(info, buffer, &y, x, length);
		while (y < length)
		{
			if (is_chain(info, buffer, &y))
			break;
			y++;
		}

		x = y + 1;
		if (x >= length)
		{
			x = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p;
		return (_strlen(p));
	}

	*buffer_p = buffer;
	return (z);
}

/**
 * read_buf - a function reads data from the file descriptor into a buffer.
 * @info: A pointer to a structure containing information about the program.
 * @buf: A pointer to the buffer where data is read.
 * @i: A pointer to the size of the buffer.
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t z = 0;

	if (*i)
		return (0);
	z = read(info->readfd, buf, READ_BUF_SIZE);
	if (z >= 0)
		*i = z;
	return (z);
}

/**
 * _getline - a function that reads a line from the input, handling buffer
 *		reallocation.
 * @info: A pointer to a structure containing information about the program.
 * @ptr: A pointer to the buffer for storing the input line.
 * @length: A pointer to the length of the buffer.
 * Return: The total number of characters read, or -1 on End of File (EOF).
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t x, len;
	size_t a;
	ssize_t z = 0, sum = 0;
	char *p = NULL, *new_p = NULL, *ch;

	p = *ptr;
	if (p && length)
		sum = *length;
	if (x == len)
		x = len = 0;

	z = read_buf(info, buffer, &len);
	if (z == -1 || (z == 0 && len == 0))
		return (-1);

	ch = _strchr(buffer + x, '\n');
	a = ch ? 1 + (unsigned int)(ch - buffer) : len;
	new_p = _realloc(p, sum, sum ? sum + a : a + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (sum)
		_strncat(new_p, buffer + x, a - x);
	else
		_strncpy(new_p, buffer + x, a - x + 1);

	sum += a - x;
	x = a;
	p = new_p;

	if (length)
		*length = sum;
	*ptr = p;
	return (sum);
}

/**
 * sigintHandler - a function that signal handler for handling SIGINT (Ctrl+C).
 * @sig_num: The signal number.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
