#ifndef _GEORGE_H_
#define _GEORGE_H_

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

/* interactive.c */
int is_shell_interactive(info_t *shellInfo);
int is_character_delimiter(char c, const char *delimiters);
int is_alpha_character(int c);
int string_to_integer(char *str);

/* shelltokens.c */
char **split_string_by_delim(char *inputStr, char delimiter);
char **split_string_ignore_repeat_delim(char *inputStr, char *delimiters);

#endif
