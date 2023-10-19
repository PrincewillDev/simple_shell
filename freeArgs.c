#include "shell.h"

/**
 * free_args - Frees an array of strings
 * @argv: Pointer to array of strings
 * Return: Void
 */
void free_args(char ***argv)
{
	int i = 0;

	if ((*argv) == NULL || argv == NULL)
	{
		_printf("hsh: free_args: NULL pointer\n");
		return;
	}

	while ((*argv)[i] != NULL)
	{
		free((*argv)[i]);
		(*argv)[i] = NULL;
		i++;
	}

	free(*argv);
	*argv = NULL;
}
