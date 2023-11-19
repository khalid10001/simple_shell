#include "shell.h"

/**
 * list_len - a function that calculates the length of a linked list.
 * @h: A pointer to the head of the linked list.
 * Return: The number of nodes in the linked list.
 */
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

/**
 * list_to_strings - a function that converts a linked list of strings into
 *			an array of strings.
 * @head: A pointer to the head of the linked list.
 * Return: An array of strings, or NULL on failure.
 */
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

/**
 * print_list - a function that prints the nodes of a linked list with
 *		their numbers.
 * @h: A pointer to the head of the linked list.
 * Return: The number of nodes in the linked list.
 */
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

/**
 * node_starts_with - a function that finds the first node in a linked list
 *		with a string prefix.
 * @node: A pointer to the head of the linked list.
 * @prefix: The prefix to search for in the string.
 * @c: The character to match after the prefix (or -1 for any character).
 * Return: A pointer to the found node, or NULL if not found.
 */
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

/**
 * get_node_index - a function that gets the index of a node in a linked list.
 * @head: A pointer to the head of the linked list.
 * @node: A pointer to the node whose index is sought.
 * Return: The index of the node, or -1 if not found.
 */
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
