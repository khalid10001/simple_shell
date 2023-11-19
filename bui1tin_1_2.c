#include "shell.h"

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

int unset_alias(info_t *info, char *str)
{
	char *ptr, ch;
	int r;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	r = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = ch;
	return (r);
}

int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

int print_alias(list_t *node)
{
	char *ptr = NULL, *x = NULL;

	if (node)
	{
	ptr = _strchr(node->str, '=');
	for (x = node->str; x <= ptr; x++)
		_putchar(*x);
	_putchar('\'');
	_puts(ptr + 1);
	_puts("'\n");
	return (0);
	}
	return (1);
}

int _myalias(info_t *info)
{
	int x = 0;
	char *ptr = NULL;
	list_t *nd = NULL;

	if (info->argc == 1)
	{
		nd = info->alias;
	while (nd)
	{
		print_alias(nd);
		nd = nd->next;
	}
	return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
	ptr = _strchr(info->argv[x], '=');
	if (ptr)
		set_alias(info, info->argv[x]);
	else
		print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}
