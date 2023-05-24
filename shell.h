#ifndef SHELL_H
#define SHELL_H

#define BUFSIZE 1024
#define NEWLINE '\n'
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define DELIM_T " \t\n\a\r"

/**
 * struct path - The path's linked list
 * @str: a variable
 * @next: the next struct path
 */
typedef struct path
{
	char *str;
	struct path *next;
} path_l;

/**
 * struct alias - aliases linked list
 * @name: alias' name
 * @value: alias' value
 * @next: next alias
 */
typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} alias_l;

/**
 * struct data - shell data structure
 * @_environ: Default shell environment copy
 * @alias: aliases linked list
 * @arr: arguments array
 * @av: arguments vector
 * @builtin: confirms a builtin command
 * @interact: 1 for  interactive shell, 0 - non interactive
 * @length: line's length
 * @line: line of all commands
 * @path: path linked list
 * @pid: process id of the shell
 * @status: shell status
 */
typedef struct data
{
	alias_l *alias;
	char **_environ;
	char **arr;
	char **av;
	char *line;
	int builtin;
	int interact;
	int status;
	path_l *path;
	pid_t pid;
	size_t length;
} sh_data;

/**
 * struct built_in - builtin functions struct
 * @str: the command string
 * @func: function pointer for the specific command
 */
typedef struct built_in
{
	char *str;
	int (*func)(sh_data *);
} built_in;

alias_l *add_alias(alias_l **, char *, char *);
void logical_ops(char *line, ssize_t *new_len);
int _alias(sh_data *);
int print_alias(sh_data *, char *);
int print_all_alias(sh_data *);
int set_alias(sh_data *, char *);
void check_alias(sh_data *);
void free_aliases(alias_l *);
int _cd(sh_data *);
void mod_dir(sh_data *, char *, char *);
int _env(sh_data *);
char *mod_env(sh_data *);
int my_exit(sh_data *);
int _set(sh_data *);
int _unset(sh_data *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(char *);
char *_itoa(int);
char *_strtok(char *, const char *);
int _atoi(char *);
int _isdigit(char *);
int _strcmp(char *, char *);
int _strlen(char *);
void *_memchr(register const void *, int, size_t);
void *_realloc(void *, unsigned int, unsigned int);
void _memcpy(void *, const void *, unsigned int);
ssize_t _getline(char **, size_t *, FILE *);
void insert_line(char **, size_t *n, char *, size_t);
void reverse_str(char *);
void free_arr2(char **);
void free_list(path_l *);
int get_len(int);
path_l *add_node_end(path_l **, char *);
path_l *path_to_list(sh_data *);
size_t print_list(const path_l *);
void print_path_dir(void);
extern char **environ;
char **get_commands(sh_data *, char *, size_t);
char *check_shell(sh_data *);
char *_getenv(sh_data *, char *);
char *search_path(path_l *, char *);
int (*get_func(char **))(sh_data *);
void loop_shell(sh_data *);
void non_interact_mode(sh_data *);
int rm_comments(char **);
void expand_var(sh_data *);
int cd_err(sh_data *, int);
void help_exit(void);

#endif
