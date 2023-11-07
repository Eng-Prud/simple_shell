#include "shell.h"

/**
 * strcat_cd - concatenates the message for cd error
 * @datash: data relevant
 * @msg: the message to print
 * @error: the output message
 * @ver_str: counter lines
 * Return: error message
 */

char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal = malloc(3);
		illegal[0] = '-';
		illegal[1] = datash->args[1][1];
		illegal[2] = '\0';
		_strcat(error, illegal);
		free(illegal);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - the error message for cd command
 * @datash: data relevant
 * Return: Error message
 */

char *error_get_cd(data_shell *datash)
{
	int len, len_id;
	char *error, *ver_str, *message;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		message = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		message = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(ver_str) + _strlen(message) + len_id + 5;
	error = malloc(sizeof(char) * (len + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(datash, message, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - the error message for command not found
 * @datash: data relevant
 * Return: Error message
 */

char *error_not_found(data_shell *datash)
{
	int len;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell - error message for exit in get_exit
 * @datash: data relevant
 * Return: Error message
 */

char *error_exit_shell(data_shell *datash)
{
	int len;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
