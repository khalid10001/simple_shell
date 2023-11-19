#include "shell.h"

int hsh(info_t *info, char **av)
{
	ssize_t z = 0;
	int bltin_ret = 0;

	while (z != -1 && bltin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		z = get_input(info);
		if (z != -1)
		{
			set_info(info, av);
			bltin_ret = find_builtin(info);
			if (bltin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (bltin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bltin_ret);
}

int find_builtin(info_t *info)
{
	int x, bltin_ret = -1;
	builtin_table bltintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; bltintbl[x].type; x++)
		if (_strcmp(info->argv[0], bltintbl[x].type) == 0)
		{
			info->line_count++;
			bltin_ret = bltintbl[x].func(info);
			break;
		}
	return (bltin_ret);
}

void find_cmd(info_t *info)
{
	char *pth = NULL;
	int x, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	pth = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (pth)
	{
		info->path = pth;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

void fork_cmd(info_t *info)
{
	pid_t chd_pid;

	chd_pid = fork();
	if (chd_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (chd_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
