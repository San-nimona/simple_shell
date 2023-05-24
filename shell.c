#include "shell.h"
/**
 * get_func - gets functions for the builtin commands
 * @arr: splits the line into arguments
 * Return: the builtin command function
 */
int (*get_func(char **arr))(sh_data *)
{
	built_in sh[] = {
		{"exit", _exit},
		{"env", _env},
		{"setenv", _set},
		{"unsetenv", _unset},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	int i = 0;

	if (arr != NULL)
	{
		while (sh[i].func != NULL)
		{
			if (_strcmp(sh[i].str, arr[0]) == 0)
			{
				return (sh[i].func);
			}
			else
				i++;
		}
	}

	return (NULL);
}

/**
 * non_interact_mode - running shell in a non-interactive mode
 * @shell: data struct of shell
 * Return: success or fail
 */
void non_interact_mode(sh_data *shell)
{
	char *path;

	shell->interact = 0;
	for (; ;)
	{
		path = check_shell(shell);
		if (!path && shell->builtin == 0)
			_exit(shell);
		else if (!path && shell->builtin == 1)
			continue;

		shell->builtin = 0;
		shell->pid = fork();
		if (shell->pid == 0)
		{
			shell->status = execve(path, shell->arr, shell->_environ);
			if (shell->status == -1)
			{
				write(STDERR_FILENO, shell->av[0], _strlen(shell->av[0]));
				write(STDERR_FILENO, ": ", 2);
				write(STDERR_FILENO, shell->arr[0], _strlen(shell->arr[0]));
				write(STDERR_FILENO, ": Permission denied\n", 20);
				free(path);
				shell->status = 13;
				_exit(shell);
			}
		}
		else
		{
			wait(&shell->status);
			shell->status = WEXITSTATUS(shell->status);
		}
		free_arr2(shell->arr);
		free(path);
	}
}

/**
 * loop_shell - Looping the shell
 * @shell: data of the shell
 *
 */
void loop_shell(sh_data *shell)
{
	char *path;

	if (shell->av[1])
		exit(98);
	else if (!isatty(STDIN_FILENO))
		non_interact_mode(shell);
	else
	{
		for (; ;)
		{
			write(STDOUT_FILENO, "($) ", 4);
			fflush(stdout);
			path = check_shell(shell);
			if (!path)
				continue;
			shell->pid = fork();
			if (shell->pid == 0)
			{
				shell->status = execve(path, shell->arr, shell->_environ);
				if (shell->status == -1)
				{
					write(STDERR_FILENO, shell->av[0], _strlen(shell->av[0]));
					write(STDERR_FILENO, ": ", 2);
					write(STDERR_FILENO, shell->arr[0], _strlen(shell->arr[0]));
					write(STDERR_FILENO, ": Permission denied\n", 20);
					free(path);
					shell->status = 13;
					_exit(shell);
				}
			}
			else
			{
				wait(&shell->status);
				shell->status = WEXITSTATUS(shell->status);
			}
			free_arr2(shell->arr);
			free(path);
		}
	}
}

/**
 * check_shell - confirms commands, paths and builtins
 * @shell: shell data structure pointer
 *
 * Return: 0 or the path
 */
char *check_shell(sh_data *shell)
{
	int (*built_in_func)(sh_data *sh);
	char *path;

	shell->arr = get_commands(shell, shell->line, shell->length);
	if (!shell->arr)
	{
		free(shell->line);
		return (NULL);
	}
	check_alias(shell);
	expand_var(shell);
	built_in_func = get_func(shell->arr);

	if (built_in_func != NULL)
	{
		shell->status = built_in_func(shell);
		if (shell->arr != NULL)
			free_arr2(shell->arr);
		shell->builtin = 1;
		return (NULL);
	}
	path = search_path(shell->path, shell->arr[0]);

	if (!path)
	{
		write(STDERR_FILENO, shell->av[0], _strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->arr[0], _strlen(shell->arr[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		shell->status = 2;
		free_arr2(shell->arr);
		free(path);
		return (NULL);
	}
	return (path);
}

/**
 * main - Runs the shell
 * @ac: Argument count
 * @av: Arguments vector
 * @env: environment variables
 *
 * Return: 0
 */
int main(int ac, char **av, char **env)
{
	sh_data shell;
	int i = 0;

	shell.line = NULL;
	shell.length = 0;
	shell.interact = 1;
	shell.pid = getpid();
	shell.status = 0;
	shell.builtin = 0;
	shell.arr = NULL;
	shell.alias = NULL;
	(void) env;

	shell.av = malloc(sizeof(char *) * (ac + 1));
	while (av[i])
	{
		shell.av[i] = my_strdup(av[0]);
		i++;
	}
	shell.av[i] = NULL;
	for (i = 0; environ[i]; i++)
		;

	shell._environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
		shell._environ[i] = my_strdup(environ[i]);
	shell._environ[i] = NULL;

	shell.path = path_to_list(&shell);

	loop_shell(&shell);

	return (0);
}
