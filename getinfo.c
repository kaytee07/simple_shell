#include "shell.h"

/**
 * get_environ - Returns a string array copy of the current environment variables.
 * @info: Structure containing potential arguments.
 *
 * Return: The string array copy of the current environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed) {
		/* Free the existing environment variable array. */
		free_string_array(info->environ);
		/* Convert the environment list to a string array. */
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return info->environ;
}

/**
 * _unsetenv - Remove an environment variable from the list.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to be removed.
 *
 * Return: 1 on successful deletion, 0 otherwise.
 */
int _unsetenv(info_t *info, const char *var)
{
	size_t i = 0;
	list_t *node = info->env, *prev = NULL;
	
	if (!node || !var)
		return 0;
	
	while (node) {
		char *p = starts_with(node->str, var);
		if (p && *p == '=') {
			/* If the variable is found, delete the node and update the list. */
			if (prev)
				prev->next = node->next;
			else
				info->env = node->next;
			free(node->str);
			free(node);
			info->env_changed = 1;
			return 1;
		}
		prev = node;
		node = node->next;
		i++;
	}
	return 0;
}

/**
 * _setenv - Initialize a new environment variable, or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The environment variable to be initialized or modified.
 * @value: The value to set the environment variable to.
 *
 * Return: 0 on success, 1 on failure.
 */
int _setenv(info_t *info, const char *var, const char *value)
{
	size_t var_len = _strlen(var), value_len = _strlen(value);
	size_t buf_len = var_len + value_len + 2;
	char *buf = malloc(buf_len);
	list_t *node = info->env;
	
	if (!buf)
		return 1;
	
	/* Concatenate the variable and value strings with a '=' separator. */
	_strcpy(buf, var);
	buf[var_len] = '=';
	_strcpy(buf + var_len + 1, value);
	
	/* Search for the variable in the list, and update its value if found. */
	while (node) {
		char *p = starts_with(node->str, var);
		if (p && *p == '=') {
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return 0;
		}
		node = node->next;
	}
	
	/* If the variable is not found, add it to the end of the list. */
	add_node_end(&(info->env), buf, buf_len);
	info->env_changed = 1;
	return 0;
}
