#include "shell.h"

/**
 * custom_perror - Prints formatted input to stderror
 * @cmd_name: Command
 * Return: void
 */
void custom_perror(char *cmd_name)
{
	char errmsg[150] = "./hsh: 1: ";
	char *error;

	switch (errno)
	{
		case EACCES:
			error= "Permission denied";
			break;
		case ENOENT:
			error= "not found";
			break;
		case ENOTDIR:
			error= "Not a directory";
			break;
		case EISDIR:
			error= "Is a directory";
			break;
		case EFAULT:
			error= "Bad address";
			break;
		case ELOOP:
			error= "Too many symbolic links";
			break;
		case ENOMEM:
			error= "Memory allocation error";
			break;
		case EINVAL:
			error= "Illegal number";
			break;
		default:
			error= "Unknown error";
			break;
	}

	_strcat(errmsg, cmd_name);
	_strcat(errmsg, ": ");
	if (errno == ENOENT && _strcmp(cmd_name, "_getenv") == 0)
		_strcat(errmsg, "variable not found");
	else
		_strcat(errmsg, error);
	_strcat(errmsg, "\n");

	write(STDERR_FILENO, errmsg, _strlen(errmsg));
}

/**
 * custom_perror_builtin - Handles errors to builtin commands
 * @cmd_name: Command
 * @arg: Argument
 * Return: void
 */
void custom_perror_builtin(char *cmd_name, char *arg)
{
	char errMsg[150] = "./hsh: ";

	if (_strcmp(cmd_name, "cd") == 0)
	{
		_strcat(errMsg, "1: cd: can't cd to ");
		_strcat(errMsg, arg);
		_strcat(errMsg, "\n");
	}
	else if (_strcmp(cmd_name, "exit") == 0)
	{
		_strcat(errMsg, "1: exit: Illegal number: ");
		_strcat(errMsg, arg);
		_strcat(errMsg, "\n");
	}

	write(STDERR_FILENO, errMsg, _strlen(errMsg));
}
