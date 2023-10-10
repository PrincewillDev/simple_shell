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
