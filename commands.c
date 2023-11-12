#include "shell.h"

/**
 * is_cdir - function that checks ":" if is in the current directory
 * @path: type char ptr char
 * @i: type int ptr of inde
 * Return: 1 if the path is searchable in the cd
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - function that locates a command
 * @cmd: command name
 * @_environ: environment var
 * Return: location of the command
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, p;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		p = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &p))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - function that determines if is an executable
 * @datash: data struct
 * Return: 0 if is not an executable
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int p;
	char *input;

	input = datash->args[0];
	for (p = 0; input[p]; p++)
	{
		if (input[p] == '.')
		{
			if (input[p + 1] == '.')
				return (0);
			if (input[p + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[p] == '/' && p != 0)
		{
			if (input[p + 1] == '.')
				continue;
			p++;
			break;
		}
		else
			break;
	}
	if (p == 0)
		return (0);

	if (stat(input + p, &st) == 0)
	{
		return (p);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - function that verifies if user has permissions to access
 * @dir: destination directory
 * @datash: data struct
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}
