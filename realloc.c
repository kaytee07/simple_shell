#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: pointer to the memory area
 * @b: byte to fill the memory with
 * @n: number of bytes to fill
 *
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	/* Fill the first n bytes of the memory area pointed to by s with b */
	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: pointer to the string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	/* Free each individual string pointed to by pp, then free pp itself */
	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to the previously allocated block of memory
 * @old_size: size of the previously allocated block of memory
 * @new_size: size of the new block of memory to be allocated
 *
 * Return: pointer to the new block of memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	/* Allocate a new block of memory if ptr is NULL */
	if (!ptr)
		return (malloc(new_size));
	/* Free ptr and return NULL if new_size is 0 */
	if (!new_size)
		return (free(ptr), NULL);
	/* Return ptr if old_size and new_size are equal */
	if (new_size == old_size)
		return (ptr);

	/* Allocate a new block of memory and copy data from ptr to the new block */
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);

	return (p);
}
