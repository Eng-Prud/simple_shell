#include "shell.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @link_head: head of the linked list.
 * @length_var: length of the variable.
 * @val_var: value of the variable.
 * @length_val: length of the value.
 * Return: address of the head.
 */
r_var *add_rvar_node(r_var **link_head, int length_var, char *val_var,
		int length_val)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = length_var;
	new->val = val_var;
	new->len_val = length_val;

	new->next = NULL;
	temp = *link_head;

	if (temp == NULL)
	{
		*link_head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*link_head);
}

/**
 * free_rvar_list - frees a r_var list
 * @link_head: head of the linked list.
 * Return: no return.
 */
void free_rvar_list(r_var **link_head)
{
	r_var *temp;
	r_var *curr;

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
