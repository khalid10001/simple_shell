#include "shell.h"

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t z = 0;
	size_t len_p = 0;

	if (!*len) /* If the buffer is empty, it is filled. */
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

ssize_t get_input(info_t *info)
{
	static char *buffer; /* The ';' command chain buffer */
	static size_t x, y, length;
	ssize_t z = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	z = input_buf(info, &buffer, &length);
	if (z == -1) /* End of File (EOF) */
		return (-1);
	if (length) /* Commands are remaining in the chain buffer */
	{
		y = x; /* Initialize a new iterator to the current buffer position */
		p = buffer + x; /* Get a pointer for return */

		check_chain(info, buffer, &y, x, length);
		while (y < length) /* Iterate to the semicolon or the end. */
		{
			if (is_chain(info, buffer, &y))
			break;
			y++;
		}

		x = y + 1; /* Increment beyond the null ';' character. */
		if (x >= length) /* Reached the end of the buffer? */
		{
			x = length = 0; /* Reset the position and length. */
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p; /* Pass back a pointer to the current command position. */
		return (_strlen(p)); /* Return the length of the current command. */
	}

	*buffer_p = buffer; /* Otherwise, if it's not a chain, pass back the buffer */
	return (z); /* Return the length of the buffer from _getline(). */
}

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
	if (!new_p) /* MALLOC FAILURE! */
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

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
