#include "shell.h"

/**
 * bfree -  a function that frees a dynamically allocated pointer and
 *		sets it to NULL.
 * @ptr: A pointer to the pointer to be freed.
 * Return: 1 if the pointer was freed, 0 otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
