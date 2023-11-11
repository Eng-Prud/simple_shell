#include "shell.h"

/**
 * first_char - function that finds index of first char
 * @input: input string
 * @i: index
 * Return: 1 for error 0 in other case
 */
int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}


/**
 * shell_loop - function, Loop of shell
 * @datash: data relevant
 */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$$ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * split_commands - function that splits command lines according to the
 * separators ;, | and &, and executes them
 * @datash: data struct
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop2;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop2 = exec_line(datash);
		free(datash->args);

		if (loop2 == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop2 == 0)
		return (0);
	return (1);
}

/**
 * read_line - function that reads the input string
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}

/**
 * check_vars - function that checks if the typed variable is $$ or $?
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data struct
 * Return: p
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int p, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (p = 0; in[p]; p++)
	{
		if (in[p] == '$')
		{
			if (in[p + 1] == '?')
				add_rvar_node(h, 2, st, lst), p++;
			else if (in[p + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), p++;
			else if (in[p + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[p + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[p + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[p + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[p + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + p, data);
		}
	}

	return (p);
}
