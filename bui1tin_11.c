#include "shell.h"

/**
 * _myexit - a function that handles the 'exit' command in the shell.
 * @info: A pointer to a structure containing information about the program.
 * Return: 1 if there is an exit argument with an illegal number, -2 otherwise.
 */
int _myexit(info_t *info)
{
	int check_ex;

	if (info->argv[1])  /* If there is an exit argument */
	{
		check_ex = _erratoi(info->argv[1]);
	if (check_ex == -1)
	{
		info->status = 2;
		print_error(info, "Illegal number: ");
		_eputs(info->argv[1]);
		_eputchar('\n');
		return (1);
	}
	info->err_num = _erratoi(info->argv[1]);
	return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - a function that handles the 'cd' command in the shell.
 * @info: A pointer to a structure containing information about the program.
 * Return: 0 on successful directory change, 1 if an error occurs.
 */
int _mycd(info_t *info)
{
	char *str, *direc, buf[1024];
	int chdirec_ret;

	str = getcwd(buf, 1024);
	if (!str)
	_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		direc = _getenv(info, "HOME=");
	if (!direc)
		chdirec_ret = chdir((direc = _getenv(info, "PWD=")) ? direc : "/");
	else
		chdirec_ret = chdir(direc);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
	if (!_getenv(info, "OLDPWD="))
	{
		_puts(str);
		_putchar('\n');
		return (1);
	}
	_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
	chdirec_ret = chdir((direc = _getenv(info, "OLDPWD=")) ? direc : "/");
	}
	else
		chdirec_ret = chdir(info->argv[1]);
	if (chdirec_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _myhelp - a function that displays a help message for the shell.
 * @info: A pointer to a structure containing information about the program.
 * Return: 0 always.
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}
