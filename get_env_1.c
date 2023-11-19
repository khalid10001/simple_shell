#include "shell.h"

/**
 * get_environ - a function that retrieves the environment variables as an
 *	array of strings.
 * @info: A pointer to a structure containing information about the program.
 * Return: An array of strings representing the environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - a function that unsets an environment variable.
 * @info: A pointer to a structure containing information about the program.
 * @var: The name of the environment variable to unset.
 * Return: 0 if successful, or the number of changes made.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nd = info->env;
	size_t x = 0;
	char *ptr;

	if (!nd || !var)
		return (0);

	while (nd)
	{
		ptr = starts_with(nd->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), x);
			x = 0;
			nd = info->env;
			continue;
		}
		nd = nd->next;
		x++;
	}

	return (info->env_changed);
}

/**
 * _setenv - a function that sets or updates an environment variable.
 * @info: A pointer to a structure containing information about the program.
 * @var: The name of the environment variable to set.
 * @value: The value to set for the environment variable.
 * Return: 0 if successful, 1 if memory allocation fails.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *nd;
	char *ptr;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);

	nd = info->env;

	while (nd)
	{
		ptr = starts_with(nd->str, var);
		if (ptr && *ptr == '=')
		{
			free(nd->str);
			nd->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}

	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;

	return (0);
}
