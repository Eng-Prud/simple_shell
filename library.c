#include "shell.h"

/**
 * _memcpy - function that copies info
 * @newptr: destination ptr
 * @ptr: source ptr
 * @size: size of new ptr
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int p;

	for (p = 0; p < size; p++)
		char_newptr[p] = char_ptr[p];
}

/**
 * aux_itoa - function that converts int to string
 * @n: type int num
 * Return: String
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int lenght = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	}
	while (n1 > 0)
		;
	return (buffer);
}

/**
 * get_sigint - function that handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * get_len - function that get the length of a num
 * @n: type int number
 * Return: Len of a num
 */
int get_len(int n)
{
	unsigned int q;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		q = n * -1;
	}
	else
	{
		q = n;
	}
	while (q > 9)
	{
		lenght++;
		q = q / 10;
	}

	return (lenght);
}

/**
 * without_comment - function that deletes comments from the input
 * @in: input string
 * Return: input without comments
 */
char *without_comment(char *in)
{
	int p, up_to;

	up_to = 0;
	for (p = 0; in[p]; p++)
	{
		if (in[p] == '#')
		{
			if (p == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[p - 1] == ' ' || in[p - 1] == '\t' || in[p - 1] == ';')
				up_to = p;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, p, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

