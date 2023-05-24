#include "shell.h"
/**
 * _atoi - converts str to int
 * @s: the string
 *
 * Return: int
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, i = 0, j = 1, m = 1;

	while (s[count] != '\0')
	{
		if (size > 0 && (s[count] < '0' || s[count] > '9'))
			break;

		if (s[count] == '-')
			j *= -1;

		if ((s[count] >= '0') && (s[count] <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		i = i + ((s[i] - 48) * m);
		m /= 10;
	}
	return (i * j);
}

/**
 * _itoa - changes int to string
 * @n: the number
 *
 * Return: pointer to string
 */
char *_itoa(int n)
{
	unsigned int j;
	int len = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	buffer[len] = '\0';

	if (n < 0)
	{
		j = n * -1;
		buffer[0] = '-';
	}
	else
	{
		j = n;
	}

	len--;
	do {
		buffer[len] = (j % 10) + '0';
		j = j / 10;
		len--;
	}
	while (j > 0)
		;
	return (buffer);
}
/**
 * free_list - frees a linked list
 * @head: the list
 *
 */
void free_list(path_l *head)
{
	path_l *temp = head, *second;

	if (head)
	{
		while (temp->next)
		{
			second = temp;
			temp = temp->next;
			free(second->str);
			free(second);
		}

		free(temp->str);
		free(temp);
	}
}

/**
 * free_arr2 - frees an array of arrays
 * @arr: array
 */
void free_arr2(char **arr)
{
	int j;

	if (arr != NULL)
	{
		for (j = 0; arr[j] ; j++)
			free(arr[j]);
		free(arr);
	}
}
/**
 * get_len - calculate length of num i
 * @i: the num
 * Return: num len
 */
int get_len(int i)
{
	unsigned int j;
	int len = 1;

	if (i < 0)
	{
		len++;
		j = i * -1;
	}
	else
	{
		j = i;
	}
	while (j > 9)
	{
		len++;
		j = j / 10;
	}

	return (len);
}
