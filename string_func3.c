#include "shell.h"
/**
 * _memcpy - copy data
 * @destination: string 1
 * @source: string 2
 * @size: length of str
 */
void _memcpy(void *destination, const void *source, unsigned int size)
{
	char *ptr = (char *)source;
	char *new = (char *)destination;
	unsigned int i;

	for (i = 0; i < size; i++)
		new[i] = ptr[i];
}

/**
 * _realloc - reallocates a memory seg
 * @ptr: pointer to allocated memory
 * @old_size: the old size
 * @new_size: new size to be allocated
 * Return: pointer to realloc mem
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *nptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		return (ptr);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	nptr = malloc(new_size);
	if (nptr == NULL)
		return (NULL);

	for (i = 0; i < new_size && i < old_size; i++)
		;

	memcpy(nptr, ptr, i);
	free(ptr);

	return (nptr);
}

/**
 * _isdigit - checks for digits
 * @dgt: the string
 * Return: 1 - digit, 0 - not digit
 */
int _isdigit(char *dgt)
{
	int i;

	for (i = 0; dgt[i] != '\0' ; i++)
	{
		if (dgt[i] < 48 || dgt[i] > 57)
			return (0);
	}

	return (1);
}
/**
 * _memchr - searches a char
 * @src_void: str to be searched
 * @c: the char
 * @length: string len
 */
void *_memchr(const void *src_void, int c, size_t length)
{
	const unsigned char *source = (const unsigned char *)src_void;

	while (length-- > 0)
	{
		if (*src == c)
			return ((void *)src);
		src++;
	}
	return (NULL);
}

/**
 * _strtok - tokenizes a str
 * @str: str to assign token
 * @delim: iters
 * Return: Returns a token
 */
char *_strtok(char *str, const char *delim)
{
	static char *s;
	char *ret = NULL;

	if (str != NULL)
	{
		s = str;
	}
	if (s != NULL && _strlen(s))
	{
		const size_t dlen = _strlen((char *)delim);

		while (*s && _memchr(delim, *s, dlen) != NULL)
		{
			++s;
		}
		if (*s)
		{
			ret = s;
			while (*s)
			{
				if (_memchr(delim, *s, dlen) != NULL)
				{
					break;
				}
				else
					++s;
			}
			if (*s)
			{
				s[0] = 0;
				++s;
			}
		}
	}
	return (ret);
}
