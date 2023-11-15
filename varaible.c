#include "george.h"

/**
 * is_command_delimiter - Checks if the current character in the buffer is a command delimiter.
 * @info: The parameter struct.
 * @buffer: The char buffer.
 * @position: Address of current position in buffer.
 *
 * Return: 1 if command delimiter, 0 otherwise.
 */
int is_command_delimiter(info_t *info, char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + 1] == '|')
	{
		buffer[index] = 0;
		index++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[index] == '&' && buffer[index + 1] == '&')
	{
		buffer[index] = 0;
		index++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[index] == ';') /* Found end of this command */
	{
		buffer[index] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*position = index;
	return (1);
}

/**
 * check_continue_chain - Checks if we should continue chaining based on the last status.
 * @info: The parameter struct.
 * @buffer: The char buffer.
 * @position: Address of current position in buffer.
 * @start: Starting position in buffer.
 * @length: Length of buffer.
 *
 * Return: Void.
 */
void check_continue_chain(info_t *info, char *buffer, size_t *position, size_t start, size_t length)
{
	size_t index = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[start] = 0;
			index = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[start] = 0;
			index = length;
		}
	}

	*position = index;
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *str;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		str = _strchr(node->str, '=');
		if (!str)
			return (0);
		str = _strdup(str + 1);
		if (!str)
			return (0);
		info->argv[0] = str;
	}
	return (1);
}

/**
 * replace_variables - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_variables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_str(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_str(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_str(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_str(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_str - Replaces a string.
 * @old_string: Address of the old string.
 * @new_string: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_str(char **old_string, char *new_string)
{
	free(*old_string);
	*old_string = new_string;
	return (1);
}
