#include "shell.h"

/**

_strcpy - copies a string from source to destination

@dest: the destination buffer

@src: the source buffer

Return: pointer to destination buffer
*/
char *_strcpy(char *dest, char *src)
{
int i = 0;

/* check if source and destination are same or source is NULL */
if (dest == src || src == NULL)
return (dest);

/* copy each character from source to destination until null character is reached */
while (src[i])
{
dest[i] = src[i];
i++;
}

/* add null character to the end of destination string */
dest[i] = '\0';
return (dest);
}

/**

_strdup - duplicates a string

@str: the string to duplicate

Return: pointer to the duplicated string
*/
char *_strdup(const char *str)
{
int length = 0;
char *ret;

/* check if input string is NULL */
if (str == NULL)
return (NULL);

/* calculate length of input string */
while (*str++)
length++;

/* allocate memory for new string and copy input string to it */
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;

return (ret);
}

/**

_puts - prints a string to stdout

@str: the string to print

Return: Nothing
*/
void _puts(char *str)
{
int i = 0;

/* check if string is NULL */
if (!str)
return;

/* print each character of string until null character is reached */
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**

_putchar - writes the character c to stdout

@c: The character to print

Return: On success 1.

On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

/* flush buffer if BUF_FLUSH character is encountered or buffer is full */
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}

/* add character to buffer unless it is BUF_FLUSH */
if (c != BUF_FLUSH)
buf[i++] = c;

return (1);
}
