#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Constants for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Constants for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Constants for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Configuration: 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* External environment variable */
extern char **environ;

/**
 * struct liststr - Linked list structure for strings
 *
 * @num: Numeric identifier
 * @str: String data
 * @next: Pointer to the next node in the list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Structure containing pseudo-arguments for functions
 *
 * @arg: Command argument string
 * @argv: Command argument array
 * @path: Path to the command
 * @argc: Argument count
 * @line_count: Line count
 * @err_num: Error number
 * @linecount_flag: Line count flag
 * @fname: File name
 * @env: Environment variable list
 * @history: History list
 * @alias: Alias list
 * @environ: Environment variable array
 * @env_changed: Environment changed flag
 * @status: Command execution status
 * @cmd_buf: Pointer to cmd ; chain buffer for memory management
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: File descriptor for reading
 * @histcount: History count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* Pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
	{ NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	  0, 0, 0 }

/**
 * struct builtin - Structure for built-in commands
 *
 * @type: Type of built-in command
 * @func: Pointer to the corresponding function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *info);
} builtin_table;

/* Function prototypes */

/* Shell loop functions */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* Parser functions */
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

/* Main shell loop */
int loophsh(char **);

/* Error handling functions */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* String manipulation functions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* String manipulation functions continued */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/* Utility functions for exits */
char *_strncpy(char *dest, char *str, int n);
char *_strncat(char *dest, char *str, int n);
char *_strchr(char *str, char d);
char *strchr(const char *__s, int __c);

/* Tokenization functions */
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

/* Memory management functions */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* More memory management functions */
int bfree(void **ptr);

/* Conversion and interactive functions */
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);

/* Error handling functions */
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* Built-in command functions */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/* More built-in command functions */
int _myhistory(info_t *info);
int _myalias(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);

/* Getline functions */
ssize_t get_input(info_t *info);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
ssize_t input_buf(info_t *info, char **buf, size_t *len);

/* Information handling functions */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/* Environment functions */
char *_getenv(info_t *info, const char *name);
int _myenv(info_t *info);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

/* Get environment functions */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/* History functions */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Linked list functions */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/* More linked list functions */
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* Variable handling functions */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

#endif

