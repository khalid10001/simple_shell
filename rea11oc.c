#include "shell.h"

/**
 * _memset - a function that sets the first bytes of the memory area pointed.
 * @s: Pointer to the memory area to be filled.
 * @b: The value to set (interpreted as an unsigned char).
 * @n: Number of bytes to fill.
 * Return: A pointer to the memory area 's'.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
	s[x] = b;
	return (s);
}

/**
 * ffree - a function that frees memory allocated for an array of strings
 *		and the array itself.
 * @pp: Pointer to the array of strings.
 */
void ffree(char **pp)
{
	char **t = pp;

	if (!pp)
		return;
	while (*pp)
	free(*pp++);
	free(t);
}

/**
 * _realloc - a function that reallocates memory to change the size of a
 *	previously allocated block.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: Old size of the memory block.
 * @new_size: New size to resize the memory block to.
 * Return: A pointer to the newly allocated memory block, or NULL on failure.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
