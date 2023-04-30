#include "shell.h"

/**
 * _eputs - Writes a string to stderr.
 * @str: The string to be printed.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i])
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes a character to stderr.
 * @c: The character to be printed.
 * Return: On success, returns 1.
 *         On error, returns -1 and sets errno.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putfd - Writes a character to a given file descriptor.
 * @c: The character to be printed.
 * @fd: The file descriptor to write to.
 * Return: On success, returns 1.
 *         On error, returns -1 and sets errno.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putsfd - Writes a string to a given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (str[i])
	{
		_putfd(str[i], fd);
		i++;
	}

	return (i);
}
