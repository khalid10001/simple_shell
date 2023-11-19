#include "shell.h"

/**
 * get_history_file - a function that constructs the full path to the
 *			history file.
 * @info: A pointer to a structure containing information about the program.
 * Return: A dynamically allocated string containing the full path to the
 *		history file, or NULL on failure.
 */
char *get_history_file(info_t *info)
{
	char *buffer, *direc;

	direc = _getenv(info, "HOME=");
	if (!direc)
		return (NULL);

	buffer = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, direc);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);

	return (buffer);
}

/**
 * write_history - a function that writes the command history to the
 *			history file.
 * @info: A pointer to a structure containing information about the program.
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *fname = get_history_file(info);
	list_t *nd = NULL;

	if (!fname)
	return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);

	if (fd == -1)
		return (-1);

	for (nd = info->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history - a function that reads command history from the history file.
 * @info: A pointer to a structure containing information about the program.
 * Return: The number of history entries read, or 0 on failure.
 */
int read_history(info_t *info)
{
	int x, end = 0, lincoun = 0;
	ssize_t fd, rdlength, fsize = 0;
	struct stat st;
	char *buffer = NULL, *fname = get_history_file(info);

	if (!fname)
		return (0);
	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlength = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlength <= 0)
		return (free(buffer), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
	{
		if (buffer[x] == '\n')
		{
			buffer[x] = 0;
			build_history_list(info, buffer + end, lincoun++);
			end = x + 1;
		}
	}
	if (end != x)
		build_history_list(info, buffer + end, lincoun++);
	free(buffer);
	info->histcount = lincoun;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - a function that adds a command to the history list.
 * @info: A pointer to a structure containing information about the program.
 * @buf: A pointer to the command to be added to the history.
 * @linecount: The line count associated with the command.
 * Return: 0 on success.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nd = NULL;

	if (info->history)
		nd = info->history;

	add_node_end(&nd, buf, linecount);

	if (!info->history)
		info->history = nd;

	return (0);
}

/**
 * renumber_history - a function that renews the line numbers for history
 *			entries.
 * @info: A pointer to a structure containing information about the program.
 * Return: The total number of history entries.
 */
int renumber_history(info_t *info)
{
	list_t *nd = info->history;
	int x = 0;

	while (nd)
	{
		nd->num = x++;
		nd = nd->next;
	}

	return (info->histcount = x);
}
