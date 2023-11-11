#include "shell.h"

/**
 * get_help - function that retrieves help messages according to builtin
 * @datash: data struct (args and input)
 * Return: 0
*/
int get_help(data_shell *datash)
{

	if (datash->args[1] == 0)
		aux_help_general();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(datash->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(datash->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(datash->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(datash->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(datash->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}

/**
 * rev_string - function that reverses a string
 * @s: input string
 */
void rev_string(char *s)
{
	int count = 0, p, q;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (p = 0; p < (count - 1); p++)
	{
		for (q = p + 1; q > 0; q--)
		{
			temp = *(str + q);
			*(str + q) = *(str + (q - 1));
			*(str + (q - 1)) = temp;
		}
	}
}
