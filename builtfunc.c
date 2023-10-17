#include "shell.h"

/**
 * exit_func - built in function to exit
 * @com: the command which entered by user
 */

void exit_func(char **com)
{
	int stat, i;

	if (com[1] == NULL)
	{
		free(com);
		exit(EXIT_SUCCESS);
	}

	for (i = 0; com[1][i]; i++)
	{
		if (isalpha(com[1][i])) /*0 if int, 1 if upper, 2 if lower*/
		{
			/*print that error because it's char*/
			printStr("Illegal number\n");
			break;
		}
		else
		{
			stat = atoi(com[1]);
			free(com);
			exit(stat);
		}
	}
}

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

