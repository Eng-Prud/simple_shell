#include "shell.h"

/**
 * _strcat - concatenate two strings
 * @des: des of the copied string
 * @srcs: source of string
 * Return: the des
 */
char *_strcat(char *des, const char *srcs)
{
	int i;
	int j;

	for (i = 0; des[i] != '\0'; i++)
		;

	for (j = 0; srcs[j] != '\0'; j++)
	{
		des[i] = srcs[j];
		i++;
	}

	des[i] = '\0';
	return (des);
}
/**
 * *_strcpy - Copies the string pointed to by source
 * @des: des of the copied string.
 * @srcs: the source of string.
 * Return: the des.
 */
char *_strcpy(char *des, char *srcs)
{

	size_t a;

	for (a = 0; srcs[a] != '\0'; a++)
	{
		des[a] = srcs[a];
	}
	des[a] = '\0';

	return (des);
}
/**
 * _strcmp - Function that compares two strings.
 * @s1: type1 string compared
 * @s2: type2 string compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: char.
 * Return: pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
