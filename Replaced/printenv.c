#include "shell.h"

/**
 * _printenv - Prints environment variables of a program
 * @environ: Pointer to array of environment variable strings
 * Return: 0 if success, -1 on fail
 */


int _printenv(char **environ)
{
	int i = 0;

	if (environ == NULL)
		return (-1);

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}
