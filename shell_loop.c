#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);

        // Print shell prompt if interactive mode is enabled
        if (interactive(info))
            _puts("$ ");

        // Flush output buffer
        _eputchar(BUF_FLUSH);

        // Read user input
        r = get_input(info);

        // Process user input
        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_cmd(info);
        }
        else if (interactive(info))
            _putchar('\n');

        // Free memory used by info struct
        free_info(info, 0);
    }

    // Write command history to file
    write_history(info);

    // Free memory used by info struct
    free_info(info, 1);

    // If not in interactive mode and a command failed, exit with error code
    if (!interactive(info) && info->status)
        exit(info->status);

    // If a builtin command was executed and called exit, exit with specified code
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }

    // Exit shell with success
    return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *          -2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
    int i, built_in_ret = -1;

    // Builtin command table
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    // Check if user command is a builtin command
    for (i = 0; builtintbl[i].type; i++)
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            // Update line count and execute builtin command
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    }

    return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	/* Set the path to the command name initially */
	info->path = info->argv[0];

	/* Check if linecount_flag is set */
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	/* Count the number of non-delimiter arguments */
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;

	/* If there are no non-delimiter arguments, return */
	if (!k)
		return;

	/* Try to find the command in the PATH */
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		/* Update the path to the full path found in PATH */
		info->path = path;
		/* Fork and execute the command */
		fork_cmd(info);
	}
	else
	{
		/* If the command was not found in PATH, check if it is an absolute path or a built-in command */
		if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			/* Fork and execute the command */
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			/* If the command was not found and is not a blank line, set the status to 127 and print an error message */
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - exec thread to run cmd
 * @info: the parameter
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	/* Fork a child process */
	child_pid = fork();

	/* If fork failed, print an error message and return */
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		/* Child process */
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			/* If execve failed, free the info struct and exit with the appropriate status code */
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		/* Parent process */
		/* Wait for the child process to complete and update the status */
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
