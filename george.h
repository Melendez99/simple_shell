#ifndef GEORGE_H
#define GEORGE_H

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

typedef struct 
{
    int readfd; 
} info_t;

/**
 * is_delim - checks if character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim);

/* interactive.c */
int is_shell_interactive(info_t *shellInfo);
int is_character_delimiter(char c, const char *delimiters);
int is_alpha_character(int c);
int string_to_integer(char *str);

/* shelltokens.c */
char **split_string_by_delim(char *inputStr, char delimiter);
char **split_string_ignore_repeat_delim(char *inputStr, char *delimiters);

/* builtinfunctions */
int exit_shell(info_t *shell_info);
int change_directory(info_t *shell_info);
int display_help(info_t *shell_info);

/* env.c */
int display_environment(info_t *info);
char *get_env_value(info_t *info, const char *name);
int set_environment_variable(info_t *info);
int unset_environment_variable(info_t *info);
int populate_environment_list(info_t *info);

/* loop.c */
int shellLoop(info_t *shellInfo, char **arguments);
int find_builtin(info_t *shellInfo);
void find_command(info_t *shellInfo);
void fork_command(info_t *shellInfo);

/* main_shell.c */
int main(int arg_count, char **arg_vector);

/* newline.c */
void sigintHandler(int sig_num);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int main(void);

/*shellmemory.c */
int freeAndNull(void **pointer);

/* varaible.c */
int is_command_delimiter(info_t *info, char *buffer, size_t *position);
void check_continue_chain(info_t *info, char *buffer, size_t *position, size_t start, size_t length);
int replace_alias(info_t *info);
int replace_variables(info_t *info);
int replace_str(char **old_string, char *new_string);

/* path.c */
int is_executable(info_t *info, char *file_path);
char *copy_characters(char *src_string, int start_idx, int end_idx);
char *find_cmd_path(info_t *info, char *path_str, char *command);

/* environ.c */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

#endif /* GEORGE_h */
