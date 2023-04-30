#include "shell.h"


/**
 * is_cmd - shows if file is an executable commandof
 * @info: the struct info
 * @path: path of the  file
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    if (!path || stat(path, &st))
        return (0);

    return (S_ISREG(st.st_mode));
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting of the index
 * @stop: stopping of the index
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    char *buf = malloc(stop - start + 1);

    if (!buf)
        return (NULL);

    int i, k;
    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];

    buf[k] = '\0';
    return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    if (!pathstr)
        return (NULL);

    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }

    char *path = NULL;
    char *curr_pos = pathstr;
    int len = _strlen(cmd);

    while (*curr_pos)
    {
        char *next_pos = _strchr(curr_pos, ':');
        if (!next_pos)
            next_pos = curr_pos + _strlen(curr_pos);

        int path_len = next_pos - curr_pos;
        int total_len = path_len + 1 + len;

        path = malloc(total_len + 1);
        if (!path)
            return (NULL);

        _strncpy(path, curr_pos, path_len);
        path[path_len] = '/';
        _strncpy(path + path_len + 1, cmd, len);
        path[total_len] = '\0';

        if (is_cmd(info, path))
            return (path);

        curr_pos = next_pos;
        if (*next_pos)
            curr_pos++;
        bfree((void **)&path);
    }

    return (NULL);
}
