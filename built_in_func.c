#include "george.h"

/**
 * exit_shell - Exits the shell with a given status.
 * @shell_info: Structure containing potential arguments.
 *
 * Return: 1 if error, 0 otherwise.
 */
int exit_shell(info_t *shell_info)
{
	int exit_status;

	if (shell_info->arguments[1])
	{
		exit_status = error_atoi(shell_info->arguments[1]);
		if (exit_status == -1)
		{
			shell_info->status = 2;
			print_error(shell_info, "Illegal number: ");
			_error_puts(shell_info->arguments[1]);
			_error_putchar('\n');
			return 1;
		}
		shell_info->error_number = error_atoi(shell_info->arguments[1]);
		return -2;
	}

	shell_info->error_number = -1;
	return -2;
}

/**
 * change_directory - Changes the current directory of the process.
 * @shell_info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int change_directory(info_t *shell_info)
{
	char *directory, buffer[1024];
	int change_dir_ret;

	char *current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!shell_info->arguments[1])
	{
		directory = _get_env(shell_info, "HOME=");
		if (!directory)
			change_dir_ret = chdir((directory = _get_env(shell_info, "PWD=")) ? directory : "/");
		else
			change_dir_ret = chdir(directory);
	}
	else if (_strcmp(shell_info->arguments[1], "-") == 0)
	{
		if (!_get_env(shell_info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return 1;
		}
		_puts(_get_env(shell_info, "OLDPWD="));
		_putchar('\n');
		change_dir_ret = chdir((directory = _get_env(shell_info, "OLDPWD=")) ? directory : "/");
	}
	else
		change_dir_ret = chdir(shell_info->arguments[1]);

	if (change_dir_ret == -1)
	{
		print_error(shell_info, "can't cd to ");
		_error_puts(shell_info->arguments[1]);
		_error_putchar('\n');
	}
	else
	{
		_set_env(shell_info, "OLDPWD", _get_env(shell_info, "PWD="));
		_set_env(shell_info, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * display_help - Displays help information.
 * @shell_info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int display_help(info_t *shell_info)
{
	(void)shell_info;

	_puts("help call works. Function not yet implemented \n");
	return 0;
}
