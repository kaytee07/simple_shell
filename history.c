#include "shell.h"

/**
 * get_history_file - gets the file of history
 * @info: a struct
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
    char *dir = _getenv(info, "HOME=");
    if (!dir) {
        return NULL;
    }
    char *filename = NULL;
    int len = snprintf(NULL, 0, "%s/%s", dir, HIST_FILE);
    if (len < 0) {
        free(dir);
        return NULL;
    }
    filename = malloc(len + 1);
    if (!filename) {
        free(dir);
        return NULL;
    }
    snprintf(filename, len + 1, "%s/%s", dir, HIST_FILE);
    free(dir);
    return filename;
}


/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read the history from the file
 * @info: the parameter struct
 * Return: success, 0 otherwise
 */
int read_history(info_t *info)
{
    char *filename = get_history_file(info);
    if (!filename) {
        return 0;
    }
    FILE *fp = fopen(filename, "r");
    free(filename);
    if (!fp) {
        return 0;
    }
    int linecount = 0;
    char buf[MAX_LINE_LENGTH];
    while (fgets(buf, sizeof(buf), fp)) {
        buf[strcspn(buf, "\n")] = '\0';  // remove trailing newline
        build_history_list(info, buf, linecount++);
    }
    fclose(fp);
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX) {
        delete_node_at_index(&(info->history), 0);
    }
    renumber_history(info);
    return info->histcount;
}


/**
 * build_history_list - adds entry to a linkedlist
 * @info: Struct args
 * @buf: buffs
 * @linecount: the line count of the history
 * Return: 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 * Return: count of history
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
