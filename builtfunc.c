#include "shell.h"

/**
 * exit_func - built in function to exit
 * @tok: the command which entered by user
 */

void exit_func(char **tok)
{
	int st, i;

	if (tok[1] == NULL)
	{
		free(tok);
		exit(EXIT_SUCCESS);
	}

	for (i = 0; tok[1][i]; i++)
	{
		if (isalpha(tok[1][i])) /*0 if int, 1 if upper, 2 if lower*/
		{
			/*print that error because it's char*/
			printStr("Illegal number\n");
			break;
		}
		else
		{
			st = atoi(tok[1]);
			free(tok);
			exit(st);
		}
	}
}
