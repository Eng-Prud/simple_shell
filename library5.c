#include "shell.h"

/**
 * _strtok - function that splits string by some delimiter
 * @str: input string
 * @delim: delimiter
 * Return: split string
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int p, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		p = _strlen(str);
		str_end = &str[p]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (p = 0; delim[p]; p++)
		{
			if (*splitted == delim[p])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - define if string passed is a num
 * @s: input string
 * Return: 1 if string is a num 0 if otherwise
 */
int _isdigit(const char *s)
{
	unsigned int p;

	for (p = 0; s[p]; p++)
	{
		if (s[p] < 48 || s[p] > 57)
			return (0);
	}
	return (1);
}

/**
 * check_env - function that checks if the typed variable is an env variable
 * @h: head of linked list
 * @in: input string
 * @data: data struct
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, p, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (p = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, p, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[p] == _envr[row][chr])
				p++;
			else
				break;
		}
	}

	for (p = 0; in[p]; p++)
	{
		if (in[p] == ' ' || in[p] == '\t' || in[p] == ';' || in[p] == '\n')
			break;
	}

	add_rvar_node(h, p, NULL, 0);
}

/**
 * bring_line - function that assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - function that reads input from stream
 * @lineptr: buffer that stores input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: num of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int p;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		p = read(STDIN_FILENO, &t, 1);
		if (p == -1 || (p == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (p == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (p != 0)
		input = 0;
	return (retval);
}
