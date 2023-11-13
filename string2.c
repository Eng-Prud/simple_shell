#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @sp: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *sp)
{
	int len;

	for (len = 0; sp[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * _strdup - duplicates a string in the heap memory.
 * @sp: Type char pointer string
 * Return: duplicated string.
 */
char *_strdup(const char *sp)
{
	char *new;
	size_t len;

	len = _strlen(sp);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, sp, len + 1);
	return (new);
}
