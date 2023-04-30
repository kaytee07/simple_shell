#include "shell.h"

/**
 * get_environ - Returns a string array copy of the current environment variables.
 * @info: Structure containing potential arguments.
 *
 * Return: The string array copy of the current environment variables.
 */
char **get_environ(info_t *info)
{
	/* If info->environ doesn't exist or has been modified, create a new one. */
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable from the list.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to be removed.
 *
 * Return: 1 on successful deletion, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	/* Iterate over each node in the list, searching for the specified variable. */
	while (node)
	{
		/* Check if the current node's string starts with the specified variable. */
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			/* If the variable is found, delete the node and update the list. */
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to be initialized or modified.
 * @value: The value to set the environment variable to.
 *
 * Return: 0 on success, 1 on failure.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	/* Allocate memory for the new environment variable string. */
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	/* Concatenate the variable and value strings with a '=' separator. */
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	/* Search for the variable in the list, and update its value if found. */
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	/* If the variable is not found, add it to the end of the list. */
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

