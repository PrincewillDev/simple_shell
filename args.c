#include "shell.h"

/**
 * linetoargs - Builds the argument vector of a program
 * @cmdline: Address of command line to tokenize
 * @argv: Pointer to argument vector
 * Return: void
 */
int linetoargs(char **cmdline, char ***argv)
{
	int i, argc = 0, quotes = 0;
	char *tok = NULL, *tok2 = NULL, *cmdlinecp;
	const char delim[] = " \n";

	if (cmdline == NULL || *cmdline == NULL || argv == NULL)
	{
		perror("hsh: linetoargs:");
		return (-1);
	}

	/* Calculate argument count */
	cmdlinecp = _strdup(*cmdline);
	if (cmdlinecp == NULL)
	{
		perror("hsh: linetoargs:");
		return (-1);
	}
	tok = strtok(cmdlinecp, delim);
	if (tok == NULL)
	{
		free(cmdlinecp);
		return (-1);
	}
	while (tok)
	{
		argc++;
		tok = strtok(NULL, delim);
	}
	free(cmdlinecp);
	cmdlinecp = NULL;

	/* Build argument vector */
	*argv = malloc(sizeof(char *) * (argc + 1));
	if (*argv == NULL)
	{
		perror("hsh: linetoargs:");
		return (-1);
	}
	cmdlinecp = _strdup(*cmdline);
	if (cmdlinecp == NULL)
	{
		perror("hsh: linetoargs:");
		free(*argv);
		argv = NULL;
		return (-1);
	}

	/* Handle quotes */
	for (i = 0; cmdlinecp[i] != '\0'; i++)
	{
		if (cmdlinecp[i] == '"')
			quotes = 1;
		if (quotes == 1 && cmdlinecp[i] == '#')
		{
			cmdlinecp[i] = '\0';
			break;
		}
	}
	tok2 = strtok(cmdlinecp, delim);
	for (i  = 0; tok2 != NULL && i < argc; i++)
	{
		(*argv)[i] = _strdup(tok2);
		if ((*argv)[i] == NULL)
		{
			perror("hsh: linetoargs:");
			free_args(argv);
			free(cmdlinecp);
			cmdlinecp = NULL;
			return (-1);
		}
		tok2 = strtok(NULL, delim);
	}
	(*argv)[argc] = NULL;
	free(cmdlinecp);
	cmdlinecp = NULL;

	return (argc);
}
