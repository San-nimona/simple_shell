#include "shell.h"

/**
 * _cd - changes the shell’s working directory
 * @shell: struct for shell data
 *
 * Return: an exit value
 */
int _cd(sh_data *shell)
{
	int m, n = 0;
	char *new_pwd, *old_pwd = _getenv(shell, "PWD");

	if (shell->arr[1] == NULL)
	{
		free_arr2(shell->arr);
		shell->arr = malloc(sizeof(char *) * 3);
		shell->arr[0] = _strdup("cd");
		shell->arr[1] = _getenv(shell, "HOME");
		shell->arr[2] = NULL;
	}
	else if (_strcmp(shell->arr[1], "-") == 0)
	{
		free(shell->arr[1]);
		shell->arr[1] = _getenv(shell, "OLDPWD");
		n++;
	}
	if (shell->arr[1] == NULL)
		n = cd_err(shell, 1);
	else
	{
		m = chdir(shell->arr[1]);
		if (m == -1)
		{
			cd_err(shell, 1);
			free(old_pwd);
			return (2);
		}
	}
	if (n == 1)
	{
		write(STDOUT_FILENO, shell->arr[1], _strlen(shell->arr[1]));
		write(STDOUT_FILENO, "\n", 1);
	} new_pwd = getcwd(NULL, 1024);
	mod_dir(shell, "new", new_pwd);
	mod_dir(shell, "old", old_pwd);
	free(new_pwd);
	free(old_pwd);
	return (0);
}

/**
 * my_exit - exits the shell
 * @shell: shell data
 *
 * Return: exits with the shell status, or 0 if no status is specified
 */
int my_exit(sh_data *shell)
{
	int ex_it = shell->status;

	if (shell->interact == 1)
	{
		if (!_strcmp("exit", shell->arr[0]) && shell->arr[1])
		{
			shell->status = _atoi(shell->arr[1]);
			ex_it = shell->status;
		}
	}
	if (shell->path)
		free_list(shell->path);

	if (shell->alias)
		free_aliases(shell->alias);
	if (shell->av)
		free_arr2(shell->av);
	if (shell->_environ)
		free_arr2(shell->_environ);
	if (shell->arr && shell->interact == 1)
		free_arr2(shell->arr);
	if (shell->line)
		free(shell->line);

	exit(ex_it);
}

/**
 * _env - prints environment variables
 * @shell: shell data
 *
 * Return: 0
 */
int _env(sh_data *shell)
{
	int i, len;

	for (i = 0; shell->_environ[i]; i++)
	{
		len = _strlen(shell->_environ[i]);
		write(STDOUT_FILENO, shell->_environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * _set - adds or changes an environment variable
 * @shell: shell data
 *
 * Return: 0 upon success or 12 upon memory allocation failure
 */
int _set(sh_data *shell)
{
	int i, j, k = 0, check, done = 0;
	char **new_env;

	for (i = 0; shell->_environ[i]; i++)
		;
	if (shell->arr[1] == NULL || shell->arr[2] == NULL)
		return (cd_err(shell, 2));

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (12);
	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && shell->arr[1][j] != '\0')
		{
			if (shell->_environ[i][j] != shell->arr[1][j])
				check = 1;
			j++;
		}
		if (check == 0)
		{
			new_env[k] = mod_env(shell);
			k++, done = 1;
			continue;
		}
		new_env[k] = _strdup(shell->_environ[i]);
		k++;
	}
	if (done == 0)
	{
		new_env[k] = mod_env(shell);
		new_env[k + 1] = NULL;
	}
	else
		new_env[k] = NULL;
	free_arr2(shell->_environ);
	shell->_environ = new_env;
	return (0);
}

/**
 * _unset - deletes an environment variable
 * @shell: shell data
 *
 * Return: 0 if successful, -1 if not
 */
int _unset(sh_data *shell)
{
	int i, j, k = 0, check, done = 0;
	char **new_env;

	for (i = 0; shell->_environ[i]; i++)
		;
	if (shell->arr[1] == NULL)
		return (cd_err(shell, 3));

	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (12);
	for (i = 0; shell->_environ[i]; i++)
	{
		j = 0, check = 0;
		while (shell->_environ[i][j] != '=' && shell->arr[1][j] != '\0')
		{
			if (shell->_environ[i][j] != shell->arr[1][j])
				check = 1;
			j++;
		}
		if (check == 0)
		{
			done = 1;
			continue;
		}
		new_env[k] = _strdup(shell->_environ[i]);
		k++;
	}
	new_env[k] = NULL;
	if (done == 0)
	{
		perror("Environment variable does not exist\n");
		free_arr2(new_env);
		return (6);
	}
	free_arr2(shell->_environ);
	shell->_environ = new_env;
	return (0);
}
