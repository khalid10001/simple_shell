#include "shell.h"

/**
 * is_chain - a function that checks if the current position in the buffer represents
 *	a command chaining operator.
 * @info: Pointer to the info_t structure.
 * @buf: The input buffer.
 * @p: Pointer to the current position in the buffer.
 * Return: 1 if a command chaining operator is found, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t y = *p;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';') /* Found the end of this command */
	{
		buf[y] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = y;
	return (1);
}

/**
 * check_chain - a function that checks and handles command chaining
 *	based on the command buffer type.
 * @info: Pointer to the info_t structure.
 * @buf:  The input buffer.
 * @p: Pointer to the current position in the buffer.
 * @i: Current buffer position.
 * @len:  Length of the buffer.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t y = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}

	*p = y;
}

/**
 * replace_alias - a function that replaces command alias if a matching
 *	alias is found in the list.
 * @info: Pointer to the info_t structure.
 * Return: 1 if alias replacement is successful, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int k;
	list_t *nd;
	char *ptr;

	for (k = 0; k < 10; k++)
	{
		nd = node_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(nd->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - a function replaces environment variables in
 *		the command arguments.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *nd;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(info->env, &info->argv[x][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[x]), _strdup(_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));
	}
	return (0);
}
/**
 * replace_string - a function that replaces a string with a new one,
 *		freeing the old string.
 * @old: Pointer to the old string.
 * @new: Pointer to the new string.
 * Return: Always returns 1.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
