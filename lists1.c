/**
 * list_len - determines length of the linked list
 * @h: pointer to first nodes
 * Return: size of the list
 */
size_t list_len(const list_t *h)
{
	size_t i;
	for (i = 0; h; h = h->next, i++);
	return i;
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	size_t i, j;
	char **strs;
	char *str;
	list_t *node;

	if (!head)
		return (NULL);
	i = list_len(head);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0, node = head; node; node = node->next, i++)
	{
		str = _strdup(node->str);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i;
	for (i = 0; h; h = h->next, i++)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}
	return i;
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p;
	for (; node; node = node->next)
	{
		if ((p = starts_with(node->str, prefix)) && ((c == -1) || (*p == c)))
			return node;
	}
	return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the nodes
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	ssize_t i;
	for (i = 0; head; head = head->next, i++)
	{
		if (head == node)
			return i;
	}
	return -1;
}

