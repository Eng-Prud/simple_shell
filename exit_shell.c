#include "shell.h"

/**
 * exit_shell - function that exit shell
 * @datash: data relevant
 * Return: 0, success
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int digit;
	int len;
	int big_num;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		digit = _isdigit(datash->args[1]);
		len = _strlen(datash->args[1]);
		big_num = ustatus > (unsigned int)INT_MAX;
		if (!digit || len > 10 || big_num)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}
