#include "george.h"

/**
 * display_environment - prints the current environment
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int display_environment(info_t *info)
{
    print_list_str(info->env);
    return 0;
}

/**
 * get_env_value - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: Environment variable name
 *
 * Return: Pointer to the value of the environment variable
 */
char *get_env_value(info_t *info, const char *name)
{
    list_t *current_node = info->env;
    char *value;

    while (current_node)
    {
        value = starts_with(current_node->str, name);
        if (value && *value)
            return value;
        current_node = current_node->next;
    }
    return NULL;
}

/**
 * set_environment_variable - Initialize a new environment variable
 *                            or modify an existing one
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, otherwise 1
 */
int set_environment_variable(info_t *info)
{
    if (info->argc != 3)
    {
        _error_puts("Incorrect number of arguments\n");
        return 1;
    }

    if (setenv(info, info->argv[1], info->argv[2]))
        return 0;

    return 1;
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, otherwise 1
 */
int unset_environment_variable(info_t *info)
{
    int i;

    if (info->argc < 2)
    {
        _error_puts("Too few arguments\n");
        return 1;
    }

    for (i = 1; i < info->argc; i++)
        unsetenv(info, info->argv[i]);

    return 0;
}

/**
 * populate_environment_list - populates environment linked list
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, otherwise 1
 */
int populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);

    info->env = node;
    return 0;
}
