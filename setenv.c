#include "shell.h"

/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 * @vname: variable name
 * @value: value to change
 * @overwrite: overwrite variable
 * Return: state of working
 */

int _setenv(const char *vname, const char *value, int overwrite)
{
	int result;

	if (vname == NULL)
	{
		perror("Invalid Argument");
		return (-1);
	}

	if (getenv(vname) != NULL && !overwrite)
	{
		return (0);
	}

	result = setenv(vname, value, overwrite);
	if (result != 0)
	{
		fputs("Failed to set environment variable\n", stderr);
		return (-1);
	}

	return (0);
}
