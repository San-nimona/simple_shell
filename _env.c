#include "shell.h"

/**
 * _getenv - gets an environment variable’s value
 * @shell: shell data struct
 * @name: name
 * Return: the env value
 */
char *_getenv(sh_data *shell, char *name)
{
	int i, j, k, l, check;
	char *value;

	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && name[j] != '\0')
		{
			if (shell->_environ[i][j] != name[j])
				check = 1;
			j++;
		}
		if (check == 0 && shell->_environ[i][j] == '=')
		{
			for (k = j + 1, l = 0; shell->_environ[i][k]; k++, l++)
				;

			value = malloc(sizeof(char) * (l + 1));

			for (k = j + 1, l = 0; shell->_environ[i][k]; l++, k++)
				value[l] = shell->_environ[i][k];
			value[l] = '\0';
			return (value);
		}
	}

	return (NULL);
}
