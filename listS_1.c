#include "shell.h"

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *nw_hd;

	if (!head)
		return (NULL);

	nw_hd = malloc(sizeof(list_t));

	if (!nw_hd)
		return (NULL);

	_memset((void *)nw_hd, 0, sizeof(list_t));
	nw_hd->num = num;

	if (str)
	{
		nw_hd->str = _strdup(str);
		if (!nw_hd->str)
		{
			free(nw_hd);
			return (NULL);
		}
	}

	nw_hd->next = *head;
	*head = nw_hd;

	return (nw_hd);
}

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *nw_nd, *nd;

	if (!head)
		return (NULL);

	nd = *head;
	nw_nd = malloc(sizeof(list_t));

	if (!nw_nd)
		return (NULL);

	_memset((void *)nw_nd, 0, sizeof(list_t));
	nw_nd->num = num;

	if (str)
	{
		nw_nd->str = _strdup(str);
		if (!nw_nd->str)
		{
			free(nw_nd);
			return (NULL);
		}
	}

	if (nd)
	{
		while (nd->next)
		nd = nd->next;

		nd->next = nw_nd;
	}
	else
		*head = nw_nd;

	return (nw_nd);
}

size_t print_list_str(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}

	return (x);
}

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nd, *prev_nd;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nd = *head;
		*head = (*head)->next;
		free(nd->str);
		free(nd);
		return (1);
	}

	nd = *head;
	while (nd)
	{
		if (x == index)
		{
			prev_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		x++;
		prev_nd = nd;
		nd = nd->next;
	}
	return (0);
}

void free_list(list_t **head_ptr)
{
	list_t *nd, *nxt_nd, *hd;

	if (!head_ptr || !*head_ptr)
		return;

	hd = *head_ptr;
	nd = hd;
	while (nd)
	{
		nxt_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = nxt_nd;
	}

	*head_ptr = NULL;
}
