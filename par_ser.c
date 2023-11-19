#include "shell.h"

/**
 * is_cmd -  a function that checks if a given path corresponds to a
 *		regular file.
 * @info: Pointer to the info_t structure (unused).
 * @path: The path to be checked.
 * Return: 1 if the path corresponds to a regular file, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - a function that duplicates a portion of characters
 *	from a string.
 * @pathstr: The original string to extract characters from.
 * @start: The starting index of the substring.
 * @stop: The stopping index (exclusive) of the substring.
 * Return: A pointer to the duplicated substring.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int x = 0, y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buffer[y++] = pathstr[x];
	buffer[y] = 0;
	return (buffer);
}

/**
 * find_path - a function that finds the full path of a command within a
 *		given PATH string.
 * @info: Pointer to the info_t structure (unused).
 * @pathstr: The PATH string to search for the command.
 * @cmd: The command to find.
 * Return: A pointer to the full path of the command if found,
 *		or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, current_pos = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			p = dup_chars(pathstr, current_pos, a);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[a])
				break;
			current_pos = a;
		}
		a++;
	}
	return (NULL);
}
