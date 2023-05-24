#include "shell.h"
/**
 * _strcmp - compares 2 strs
 * @str1: 1st str
 * @str2: 2nd string
 * Return: an int
 */
int _strcmp(char *str1, char *str2)
{
	int i, j;

	for (i = 0, j = 0; (str1[i] != '\0' || str2[i] != '\0'); n++)
	{
		j = str1[i] - str2[i];
		if (j != 0)
			break;
	}

	if (j < 0)
		return (-1);
	else if (j > 0)
		return (1);

	return (j);
}

/**
 * _strdup - duplicates a string
 * @str: the string to be duplicated
 *
 * Return: pointer to the new string
 */
char *_strdup(char *str)
{
	char *dup;
	size_t len;

	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	_memcpy(dup, str, len + 1);
	return (dup);
}
/**
 * _strlen - calculates str length
 * @str: the str
 * Return: the str len
 */
int _strlen(char *str)
{
	int len;

	for (len = 0; str[len] != '\0'; len++)
		;

	return (len);
}

/**
 * _strcpy - copies a string
 * @destination: pointer to new str
 * @source: pointer to the str being copied
 *
 * Return: a pointer to the new str
 */
char *_strcpy(char *destination, char *source)
{
	int i;

	for (i = 0; source[i] != '\0'; i++)
		destination[i] = source[i];

	destination[i] = '\0';
	return (destination);
}

/**
 * _strcat - concatenates 2 strings
 * @destination: string 1
 * @source: string 2
 * Return: a pointer to the concatenated string
 */
char *_strcat(char *destination, char *source)
{
	int i = 0;

	while (destination[i] != '\0')
		i++;
	for (j = 0; source[j] != '\0'; j++, i++)
		destination[i] = source[j];
	destination[i] = '\0';
	return (destination);
}
