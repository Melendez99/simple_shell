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

#endif /* GEORGE_h */
