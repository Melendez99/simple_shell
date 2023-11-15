#include "george.h"

/**
 * shellLoop - Main shell loop handling input and execution of commands.
 * @shellInfo: The parameter and return info struct.
 * @arguments: The argument vector from main().
 *
 * Return: 0 on success, 1 on error or error code.
 */
int shellLoop(info_t *shellInfo, char **arguments)
{
	ssize_t readStatus = 0;
	int builtinReturn = 0;

	while (readStatus != -1 && builtinReturn != -2)
	{
		clear_info(shellInfo);
		if (interactive(shellInfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		readStatus = get_input(shellInfo);
		if (readStatus != -1)
		{
			set_info(shellInfo, arguments);
			builtinReturn = find_builtin(shellInfo);
			if (builtinReturn == -1)
				find_command(shellInfo);
		}
		else if (interactive(shellInfo))
			_putchar('\n');
		free_info(shellInfo, 0);
	}
	write_history(shellInfo);
	free_info(shellInfo, 1);
	if (!interactive(shellInfo) && shellInfo->status)
		exit(shellInfo->status);
	if (builtinReturn == -2)
	{
		if (shellInfo->err_num == -1)
			exit(shellInfo->status);
		exit(shellInfo->err_num);
	}
	return (builtinReturn);
}

/**
 * find_builtin - Finds a builtin command in the provided table.
 * @shellInfo: The parameter and return info struct.
 *
 * Return: -1 if builtin not found, 0 if executed successfully,
 *         1 if found but not successful, -2 if signals exit().
 */
int find_builtin(info_t *shellInfo)
{
	int i, builtInReturn = -1;
	builtin_table builtinTable[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtinTable[i].type; i++)
		if (_strcmp(shellInfo->argv[0], builtinTable[i].type) == 0)
		{
			shellInfo->line_count++;
			builtInReturn = builtinTable[i].func(shellInfo);
			break;
		}
	return (builtInReturn);
}

/**
 * find_command - Finds a command in PATH.
 * @shellInfo: The parameter and return info struct.
 *
 * Return: void
 */
void find_command(info_t *shellInfo)
{
	char *cmdPath = NULL;
	int i, argCount;

	shellInfo->path = shellInfo->argv[0];
	if (shellInfo->linecount_flag == 1)
	{
		shellInfo->line_count++;
		shellInfo->linecount_flag = 0;
	}
	for (i = 0, argCount = 0; shellInfo->arg[i]; i++)
		if (!is_delim(shellInfo->arg[i], " \t\n"))
			argCount++;
	if (!argCount)
		return;

	cmdPath = find_path(shellInfo, _getenv(shellInfo, "PATH="), shellInfo->argv[0]);
	if (cmdPath)
	{
		shellInfo->path = cmdPath;
		fork_command(shellInfo);
	}
	else
	{
		if ((interactive(shellInfo) || _getenv(shellInfo, "PATH=")
			|| shellInfo->argv[0][0] == '/') && is_cmd(shellInfo, shellInfo->argv[0]))
			fork_command(shellInfo);
		else if (*(shellInfo->arg) != '\n')
		{
			shellInfo->status = 127;
			print_error(shellInfo, "not found\n");
		}
	}
}

/**
 * fork_command - Forks an exec thread to run a command.
 * @shellInfo: The parameter and return info struct.
 *
 * Return: void
 */
void fork_command(info_t *shellInfo)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(shellInfo->path, shellInfo->argv, get_environ(shellInfo)) == -1)
		{
			free_info(shellInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shellInfo->status));
		if (WIFEXITED(shellInfo->status))
		{
			shellInfo->status = WEXITSTATUS(shellInfo->status);
			if (shellInfo->status == 126)
				print_error(shellInfo, "Permission denied\n");
		}
	}
}
