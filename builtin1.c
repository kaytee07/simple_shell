#include "shell.h"

/**
 * _mycd - changes the current working directory of the shell
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *dir = NULL, *pwd = NULL, *oldpwd = NULL;

	if (info->argc == 1 || _strcmp(info->argv[1], "~") == 0)
		dir = _getenv("HOME");
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv("OLDPWD");
		if (dir == NULL)
		{
			_puts("cd: OLDPWD not set\n");
			return (1);
		}
	}
	else
		dir = info->argv[1];
	if (dir == NULL || chdir(dir) == -1)
	{
		perror("cd");
		return (1);
	}
	pwd = _getcwd();
	oldpwd = _getenv("PWD");
	if (oldpwd)
		set_env(&info->env, "OLDPWD", oldpwd);
	set_env(&info->env, "PWD", pwd);
	free(pwd);
	return (0);
}

/**
 * _myenv - prints the environment
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list(info->env);
	return (0);
}

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
int _myexit(info_t *info)
{
	int exit_code = 0;

	if (info->argc > 1)
		exit_code = _atoi(info->argv[1]);
	free_info(info);
	exit(exit_code);
}

/**
 * _myecho - displays a message
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0
 */
int _myecho(info_t *info)
{
	int i = 1;

	while (info->argv[i])
	{
		_puts(info->argv[i]);
		if (info->argv[++i])
			_putchar(' ');
	}
	_putchar('\n');
	return (0);
}

