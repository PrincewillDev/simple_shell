#include "shell.h"

/**
 * variable_replace - Handles variable replacement in shell
 * @argv: Pointer to array of shell arguments
 * Return: void
 */
void variable_replace(char ***argv)
{
	int i = 0;
	char *varName, *varValue, numStr[20] = {0};
	pid_t pid;

	while ((*argv)[i] != NULL)
	{
		if (argv == NULL || (*argv)[i] == NULL)
			return;
		if ((*argv)[i][0] == '$')
		{
			varName = (*argv)[i] + 1;
			if (varName[0] == '?')
			{
				_sprintf(numStr, "%d", status);
				free((*argv)[i]);
				(*argv)[i] = _strdup(numStr);
			}
			else if (varName[0] == '$' && varName[1] == '\0')
			{
				pid = getpid();
				_sprintf(numStr, "%d", pid);
				free((*argv)[i]);
				(*argv)[i] = _strdup(numStr);
			}
			else if (varName[0] == '\0')
			{
				free((*argv)[i]);
				(*argv)[i] = _strdup("$");
			}
			else
			{
				varValue = _getenv(varName);
				if (varValue != NULL)
				{
					free((*argv)[i]);
					(*argv)[i] = _strdup(varValue);
				}
				else
				{
					free((*argv)[i]);
					(*argv)[i] = NULL;
				}
			}
		}
		i++;
	}
}
