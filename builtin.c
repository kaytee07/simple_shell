#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: pointer to a structure containing potential arguments
 * Return: exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int exit_status = 0;

    if (info->argv[1])  /* If there is an exit argument */
    {
        exit_status = _erratoi(info->argv[1]);
        if (exit_status == -1)
        {
            /* If _erratoi fails, print error message and set exit status */
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            exit_status = 1;
        }
        /* Set error number and exit with given status */
        info->err_num = exit_status;
        exit(exit_status);
    }
    /* If no argument given, set error number and exit */
    info->err_num = -1;
    exit(exit_status);
}

/**
 * _mycd - changes the current directory of the process
 * @info: pointer to a structure containing potential arguments
 * Return: Always 0
 */
int _mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    /* If no argument given, change directory to home directory */
    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    /* If argument is "-", change directory to previous directory */
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    /* Otherwise, change directory to specified directory */
    else
        chdir_ret = chdir(info->argv[1]);

    /* If chdir fails, print error message */
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    /* Otherwise, set PWD and OLDPWD environment variables */
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * _myhelp - displays help information
 * @info: pointer to a structure containing potential arguments
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    _puts("Help information goes here.\n");
    if (0)
        _puts(*arg_array); /* temporary workaround for unused variable warning */
    return (0);
}
