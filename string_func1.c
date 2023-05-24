#include "shell.h"

/**
 * reverse_str - reverses a given str
 * @string: the string given
 */
void reverse_str(char *string)
{
	char temp;
	int i, j, k;

	for (i = 0; string[i] != '\0'; i++)
		;

	for (j = 0; j < (i - 1); j++)
	{
		for (k = j + 1; k > 0; k--)
		{
			temp = string[k];
			string[k] = string[k - 1];
			string[k - 1] = temp;
		}
	}
}

/**
 * mod_env - modifies the env
 * @shell: data of shell
 *
 * Return: the str
 */
char *mod_env(sh_data *shell)
{
	char *str;
	int i;
	int j;

	i = _strlen(shell->arr[1]);
	j = _strlen(shell->arr[2]);

	str = malloc(sizeof(char) * (i + j + 2));
	if (!str)
		return (NULL);

	_strcpy(str, shell->arr[1]);
	_strcat(str, "=");
	_strcat(str, shell->arr[2]);

	return (str);
}

/**
 * mod_dir - Changes a directory
 * @shell: shell pointer
 * @dir: directory being set
 * @newdir: a new directory
 *
 */
void mod_dir(sh_data *shell, char *dir, char *newdir)
{
	free_arr2(shell->arr);
	shell->arr = malloc(sizeof(char *) * 4);
	shell->arr[0] = _strdup("setenv");

	if (_strcmp(dir, "old") == 0)
		shell->arr[1] = _strdup("OLDPWD");
	else if (_strcmp(dir, "new") == 0)
		shell->arr[1] = _strdup("PWD");

	shell->arr[2] = _strdup(newdir);
	shell->arr[3] = NULL;

	_set(shell);
}

/**
 * cd_err - prints the error
 * @shell: data of shell
 * @n: the number of the error
 * Return: nothing
 */
int cd_err(sh_data *shell, int n)
{
	if (n == 1)
	{
		write(STDERR_FILENO, shell->av[0], _strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[0], 2);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[1], _strlen(shell->arr[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (1);
	}

	if (n == 2)
	{
		write(STDERR_FILENO, shell->av[0], _strlen(shell->av[0]));
		write(STDERR_FILENO, ": Usage: setenv VARIABLE VALUE\n", 31);
		return (1);
	}

	if (n == 3)
	{
		write(STDERR_FILENO, shell->av[0], _strlen(shell->av[0]));
		write(STDERR_FILENO, ": Usage: unsetenv VARIABLE\n", 27);
		return (1);
	}

	if (n == 4)
	{
		write(STDOUT_FILENO, shell->arr[1], _strlen(shell->arr[1]));
		write(STDOUT_FILENO, ": OLDPWD not set\n", 17);
		return (0);
	}

	return (1);
}
