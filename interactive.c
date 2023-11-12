#include "george.h"

/**
 * is_shell_interactive - returns true if shell is in interactive mode
 * @shellInfo: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */

int is_shell_interactive(info_t *shellInfo) 
{
    return isatty(STDIN_FILENO) && shellInfo->readfd <= 2;
}

/**
 * is_character_delimiter - checks if character is a delimiter
 * @c: the char to check
 * @delimiters: the delimiter string
 * Return: 1 if true, 0 if false
 */

int is_character_delimiter(char c, const char *delimiters) 
{
    while (*delimiters)
        if (*delimiters++ == c)
            return 1;
    return 0;
}

/**
 * is_alpha_character - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha_character(int c) 
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? 1 : 0;
}

/**
 * string_to_integer - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int string_to_integer(char *str) 
{
    int sign = 1, result = 0, output = 0;

    for (int i = 0; str[i] != '\0'; i++) 
    {	
        if (str[i] == '-')
            sign *= -1;
        else if (str[i] >= '0' && str[i] <= '9') 
	{
            result = result * 10 + (str[i] - '0');
            output = (sign == 1) ? result : -result;
        } else
            break;
 	}

    return output;
}
