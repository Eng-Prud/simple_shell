#include "shell.h"

/**
 * copy_info - function that copies info to create
 * a new env or alias
 * @name: name that is (env or alias)
 * @value: value that is (env or alias)
 * Return: A new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - function that sets an environment variable
 * @name: name of the environment var
 * @value: value of the environment var
 * @datash: data structure (environ)
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int p;
	char *var_env, *name_env;

	for (p = 0; datash->_environ[p]; p++)
	{
		var_env = _strdup(datash->_environ[p]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[p]);
			datash->_environ[p] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, p, sizeof(char *) * (p + 2));
	datash->_environ[p] = copy_info(name, value);
	datash->_environ[p + 1] = NULL;
}

/**
 * _setenv - function that compares env variables names
 * with the name passed
 * @datash: data relevant (env name and env value)
 * Return: 1 success
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - function that deletes a environment variable
 * @datash: data relevant (env name)
 * Return: 1 success
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int x, y, z;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	z = -1;
	for (x = 0; datash->_environ[x]; x++)
	{
		var_env = _strdup(datash->_environ[x]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			z = x;
		}
		free(var_env);
	}
	if (z == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (x));
	for (x = y = 0; datash->_environ[x]; x++)
	{
		if (x != z)
		{
			realloc_environ[y] = datash->_environ[x];
			y++;
		}
	}
	realloc_environ[y] = NULL;
	free(datash->_environ[z]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
