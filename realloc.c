#include "shell.h"

/**
 * _realloc - reallocates a memory block.
 * @p: pointer to the memory previously allocated.
 * @o: old size, in bytes, of the allocated pointer.
 * @n: new size, in bytes, of the new memory block.
 *
 * Return: p.
 * if n == o, returns p without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *p, unsigned int o, unsigned int n)
{
	void *new_p;

	if (p == NULL)
		return (malloc(n));

	if (n == 0)
	{
		free(p);
		return (NULL);
	}

	if (n == o)
		return (p);

	new_p = malloc(n);
	if (new_p == NULL)
		return (NULL);

	if (n < o)
		_memcpy(new_p, p, n);
	else
		_memcpy(new_p, p, o);

	free(p);
	return (new_p);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @p: double pointer to the memory previously allocated.
 * @o:old size, in bytes, of the allocated space of p.
 * @n: new size, in bytes, of the new memory block.
 *
 * Return: p.
 * if n == o, returns p without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **p, unsigned int o, unsigned int n)
{
	char **new_p;
	unsigned int i;

	if (p == NULL)
		return (malloc(sizeof(char *) * n));

	if (n == o)
		return (p);

	new_p = malloc(sizeof(char *) * n);
	if (new_p == NULL)
		return (NULL);

	for (i = 0; i < o; i++)
		new_p[i] = p[i];

	free(p);

	return (new_p);
}

