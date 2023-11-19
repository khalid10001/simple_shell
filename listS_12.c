#include "shell.h"

size_t list_len(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		h = h->next;
		x++;
	}

	return (x);
}

char **list_to_strings(list_t *head)
{
	list_t *nd = head;
	size_t x = list_len(head), y;
	char **str;
	char *s;

	if (!head || !x)
		return (NULL);

	str = malloc(sizeof(char *) * (x + 1));

	if (!str)
		return (NULL);

	for (x = 0; nd; nd = nd->next, x++)
	{
		s = malloc(_strlen(nd->str) + 1);
		if (!s)
		{
			for (y = 0; y < x; y++)
				free(str[y]);
			free(str);
			return (NULL);
		}
		s = _strcpy(s, nd->str);
		str[x] = s;
	}

	str[x] = NULL;
	return (str);
}

size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}

	return (a);
}

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);

	if (ptr && ((c == -1) || (*ptr == c)))
		return (node);

	node = node->next;
	}
	return (NULL);
}

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);

	head = head->next;
	k++;
	}

	return (-1);
}
