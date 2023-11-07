#include "shell.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sep_list.
 * @list_head: head of the linked list.
 * @splitter: separator splitter found (; | &).
 * Return: address of the head.
 */
sep_list *add_sep_node_end(sep_list **list_head, char splitter)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = splitter;
	new->next = NULL;
	temp = *list_head;

	if (temp == NULL)
	{
		*list_head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*list_head);
}

/**
 * free_sep_list - frees a sep_list
 * @list_head: head of the linked list.
 * Return: no return.
 */
void free_sep_list(sep_list **list_head)
{
	sep_list *temp;
	sep_list *curr;

	if (list_head != NULL)
	{
		curr = *list_head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*list_head = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @list_head: head of the linked list.
 * @com_line: command line.
 * Return: address of the head.
 */
line_list *add_line_node_end(line_list **list_head, char *com_line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = com_line;
	new->next = NULL;
	temp = *list_head;

	if (temp == NULL)
	{
		*list_head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*list_head);
}

/**
 * free_line_list - frees a line_list
 * @link_head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **link_head)
{
	line_list *temp;
	line_list *curr;

	if (link_head != NULL)
	{
		curr = *link_head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*link_head = NULL;
	}
}
