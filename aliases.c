#include "shell.h"

/**
 * _alias - handles the alias builtin commands
 * @shell: pointer to the shell structure
 * Return: 0 on success or appropriate err
 */
int _alias(sh_data *shell)
{
	int i, j, check, ret = 0;

	if (!shell->arr[1])
	{
		ret = print_all_alias(shell);
	}
	else
	{
		for (i = 1; shell->arr[i]; i++)
		{
			check = 0;
			for (j = 0; shell->arr[i][j]; j++)
			{
				if (shell->arr[i][j] == '=')
				{
					check = 1;
					ret = set_alias(shell, shell->arr[i]);
					break;
				}
			}
			if (check == 0)
				ret = print_alias(shell, shell->arr[i]);
		}
	}

	return (ret);
}

/**
 * set_alias - creates an alias
 * @shell: pointer to shell structure
 * @arg: of the format: name=value
 *
 * Return: 0 on success
 */
int set_alias(sh_data *shell, char *arg)
{
	char *name, *value, *str;

	str = _strdup(arg);
	name = _strtok(str, "=");
	value = _strtok(NULL, "");

	add_alias(&shell->alias, name, value);
	if (shell->alias == NULL)
	{
		write(STDERR_FILENO, shell->av[0], _strlen(shell->av[0]));
		write(STDERR_FILENO, ": Unable to add alias\n", 22);
		free(str);
		return (12);
	}

	free(str);
	return (0);
}

/**
 * print_all_alias - prints all aliases set in the current session
 * @shell: pointer to shell structure
 *
 * Return: 0 or 61
 */
int print_all_alias(sh_data *shell)
{
	alias_l *temp = shell->alias;
	char *alias;
	int len1, len2;

	if (!temp)
	{
		return (0);
	}
	while (temp)
	{
		len1 = _strlen(temp->name);
		len2 = _strlen(temp->value);
		alias = malloc(sizeof(char) * (len1 + len2 + 2));
		if (!alias)
			return (12);

		_strcpy(alias, temp->name);
		_strcat(alias, "=");
		_strcat(alias, temp->value);

		write(STDOUT_FILENO, alias, len1 + len2 + 1);
		write(STDOUT_FILENO, "\n", 1);

		free(alias);
		temp = temp->next;
	}

	return (0);
}

/**
 * print_alias - prints a specific alias
 * @shell: pointer to shell structure
 * @arg: alias’s name to print in the form: name
 *
 * Return: 0 on success
 */
int print_alias(sh_data *shell, char *arg)
{
	alias_l *temp = shell->alias;
	char *alias = NULL;
	int len1, len2;

	if (!temp)
	{
		write(STDERR_FILENO, shell->av[0], _strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[1], _strlen(shell->arr[1]));
		write(STDERR_FILENO, " not found\n", 11);
		return (1);
	}
	while (temp)
	{
		if (_strcmp(arg, temp->name) == 0)
		{
			len1 = _strlen(temp->name);
			len2 = _strlen(temp->value);
			alias = malloc(sizeof(char) * (len1 + len2 + 2));
			if (!alias)
				return (12);

			_strcpy(alias, temp->name);
			_strcat(alias, "=");
			_strcat(alias, temp->value);

			write(STDOUT_FILENO, alias, len1 + len2 + 1);
			write(STDOUT_FILENO, "\n", 1);
			free(alias);
		}
		temp = temp->next;
	}

	return (0);
}

/**
 * add_alias - adds a new node at the end of the alias_l list
 * @head: alias list pointer
 * @name: the alias’s name
 * @value: the alias’s value
 *
 * Return: address of resulting list
 */
alias_l *add_alias(alias_l **head, char *name, char *value)
{
	alias_l *list, *temp = *head;
	char *v;

	if (value[0] == 39)
		v = _strdup(value);
	else
	{
		v = malloc(sizeof(char) * (_strlen(value) + 3));
		_strcpy(v, "'");
		_strcat(v, value);
		_strcat(v, "'");
	}
	while (temp)
	{
		if (_strcmp(temp->name, name) == 0)
		{
			free(temp->value);
			temp->value = _strdup(v);
			free(v);
			return (temp);
		}
		temp = temp->next;
	}
	temp = *head;
	list = malloc(sizeof(alias_l));
	if (!list)
		return (NULL);
	list->name = _strdup(name);
	list->value = _strdup(v);
	list->next = NULL;
	if (!temp)
		*head = list;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = list;
	}
	free(v);
	return (*head);
}
