#include "shell.h"

/**
 * cd_shell - current directory changes.
 * @datarel: relevant data
 * Return: 1 on success
 */
int cd_shell(data_shell *datarel)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datarel->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(datarel);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datarel);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datarel);
		return (1);
	}

	cd_to(datarel);

	return (1);
}

/**
 * cd_dot - changes to the parent directory
 *
 * @datarel: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(data_shell *datarel)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datarel);
	dir = datarel->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, datarel);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datarel);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datarel);
	}
	datarel->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @datarel: data relevant (directories)
 * Return: no return
 */
void cd_to(data_shell *datarel)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datarel->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datarel, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datarel);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, datarel);

	free(cp_pwd);
	free(cp_dir);

	datarel->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @datarel: relevant data.
 * Return: no return
 */
void cd_previous(data_shell *datarel)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datarel->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, datarel);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datarel);
	else
		set_env("PWD", cp_oldpwd, datarel);

	p_pwd = _getenv("PWD", datarel->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datarel->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @datarel: relevant  data
 * Return: no return
 */
void cd_to_home(data_shell *datarel)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datarel->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datarel);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datarel, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datarel);
	set_env("PWD", home, datarel);
	free(p_pwd);
	datarel->status = 0;
}

