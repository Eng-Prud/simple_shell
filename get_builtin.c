#include "shell.h"

/**
 * get_builtin - function of builtin that pairs command in arg
 * @cmd: command
 * Return: function ptr of builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int p;

	for (p = 0; builtin[p].name; p++)
	{
		if (_strcmp(builtin[p].name, cmd) == 0)
			break;
	}

	return (builtin[p].f);
}
