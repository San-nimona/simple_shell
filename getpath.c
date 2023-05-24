#include "shell.h"
/**
 * search_path - find a path linked list
 * @list: path list pointer
 * @file: file to find
 *
 * Return: path name or NULL
 */
char *search_path(path_l *list, char *file)
{
	path_l *temp = list;
	char *path;
	struct stat s;

	while (temp)
	{
		path = malloc(sizeof(char) * (_strlen(temp->str) + _strlen(file) + 2));

		if (file[0] == '/')
		{
			free(path);
			if (stat(file, &s) == 0)
			{
				path = _strdup(file);
				return (path);
			}
			else
				return (NULL);
		}

		_strcpy(path, temp->str);
		_strcat(path, "/");
		_strcat(path, file);
		if (stat(path, &s) == 0)
			return (path);

		free(path);
		temp = temp->next;
	}

	return (NULL);
}
/**
 * add_node_end - adds a new node at end
 * @head: the head
 * @str: string to add to the node
 *
 * Return: pointer to new list
 */
path_l *add_node_end(path_l **head, char *str)
{
	path_l *list;
	path_l *temp;

	temp = *head;
	list = malloc(sizeof(path_l));

	if (!list)
		return (NULL);

	list->str = _strdup(str);
	list->next = NULL;

	if (!temp)
	{
		*head = list;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = list;
	}

	return (*head);
}

/**
 * path_to_list - makes a linked list of the directories
 * @shell: the struct of shell environment
 *
 * Return: a linked list to path of PATH
 */
path_l *path_to_list(sh_data *shell)
{
	char path[5] = "PATH";
	int i, j, k, check;
	path_l *head = NULL;
	char *str;

	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && path[j] != '\0')
		{
			if (shell->_environ[i][j] != path[j])
				check = 1;
			j++;
		} k = 0;
		if (check == 0)
		{
			j++;
			while (shell->_environ[i][j])
			{
				if (shell->_environ[i][j] == ':')
				{
					str[k] = '\0', k = 0;
					add_node_end(&head, str);
					free(str);
				}
				else
				{
					if (k == 0)
						str = malloc(sizeof(char) * 150);
					str[k] = shell->_environ[i][j], k++;
				} j++;
			} str[k] = '\0';
			add_node_end(&head, str);
			free(str);
			break;
		}
	} str = _getenv(shell, "PWD");
	add_node_end(&head, str);
	free(str);
	return (head);
}
/**
 * expand_var - expands a variable
 * @shell: shell structure pointer
 *
 */
void expand_var(sh_data *shell)
{
	int i, j, k;
	char *str, *value;

	for (i = 0; shell->arr[i]; i++)
	{
		if (_strcmp(shell->arr[i], "$$") == 0)
		{
			free(shell->arr[i]);
			str = _itoa(shell->pid);
			shell->arr[i] = _strdup(str);
			free(str);
		}
		else if (_strcmp(shell->arr[i], "$?") == 0)
		{
			free(shell->arr[i]);
			str = _itoa(shell->status);
			shell->arr[i] = _strdup(str);
			free(str);
		}
		else if (shell->arr[i][0] == '$')
		{
			str = malloc(sizeof(char) * _strlen(shell->arr[i]));
			for (j = 1, k = 0; shell->arr[i][j]; j++, k++)
				str[k] = shell->arr[i][j];
			str[k] = '\0';
			value = _getenv(shell, str);
			if (value == NULL)
			{
				free(value);
				free(str);
			}
			else
			{
				free(shell->arr[i]);
				free(str);
				shell->arr[i] = _strdup(value);
				free(value);
			}
		}
	}
}
