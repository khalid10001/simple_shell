#include "shell.h"

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

char *_getenv(info_t *info, const char *name)
{
	list_t *nd = info->env;
	char *ptr;

	while (nd)
	{
	ptr = starts_with(nd->str, name);
	if (ptr && *ptr)
		return (ptr);
	nd = nd->next;
	}
	return (NULL);
}

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

int _myunsetenv(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
	_eputs("Too few arguments.\n");
	return (1);
	}
	for (k = 1; k <= info->argc; k++)
	_unsetenv(info, info->argv[k]);

	return (0);
}

int populate_env_list(info_t *info)
{
	list_t *nd = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&nd, environ[x], 0);
	info->env = nd;
	return (0);
}
