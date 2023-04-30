#include "shell.h"

/**

*add_node - Adds a node to the start of a linked list
*@head: Address of a pointer to the head node of the list
*@str: The string to be stored in the new node
*@num: The node index used by histor
*/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end
 * @head: pointer to the head node
 * @str: string field of node
 * @num: node index by history to be used
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = NULL;
	if (*head)
	{
		list_t *last_node = *head;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return new_node;
}


/**
 * print_list_str - print the string  element of the list_t linked_list
 * @h: pointer to the first node
 * Return: size of the list
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;
	
	while (h)
	{
		if (h->str)
		{
			fwrite(h->str, strlen(h->str), 1, stdout);
			fputc('\n', stdout);
		}
		else
		{
			fputs("(nil)\n", stdout);
		}
		h = h->next;
		count++;
	}

	return count;
}


/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = node->next;
		free(node->str);
		free(node);
		return (1);
	}

	prev_node = *head;
	node = (*head)->next;
	while (node && index > 1)
	{
		prev_node = node;
		node = node->next;
		index--;
	}

	if (!node)
		return (0);

	prev_node->next = node->next;
	free(node->str);
	free(node);
	return (1);
}


/**
 * free_list - frees nodes of the list
 * @head_ptr: pointer to the head node
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node;

	if (!head_ptr || !*head_ptr)
		return;

	node = *head_ptr;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
