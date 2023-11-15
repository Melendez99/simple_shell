#include "george.h"

/**
 * get_environ - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 *
 * Return: Pointer to the string array (environ).
 */
char **get_environ(info_t *info) {
    if (!info->environ || info->env_changed) {
        free_string_array(info->environ); // Free the previously allocated environment strings
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }
    return info->environ;
}

/**
 * _unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * @var: The string env var property.
 *
 * Return: 1 on delete, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var) {
    if (!info->env || !var)
        return 0;

    list_t *prev = NULL;
    list_t *node = info->env;

    while (node) {
        char *p = starts_with(node->str, var);
        if (p && *p == '=') {
            if (prev)
                prev->next = node->next;
            else
                info->env = node->next;

            free(node->str);
            free(node);
            info->env_changed = 1;
            return 1;
        }
        prev = node;
        node = node->next;
    }
    return 0;
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain constant function prototype.
 * @var: The string env var property.
 * @value: The string env var value.
 *
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value) {
    if (!var || !value)
        return 0;

    char *buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return 1;

    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);

    list_t *node = info->env;

    while (node) {
        char *p = starts_with(node->str, var);
        if (p && *p == '=') {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }

    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return 0;
}
