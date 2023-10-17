#include "shell.h"

extern char **environ;

int _unsetenv(const char *vname)
{
	int i, j;

	if (vname == NULL)
	{
		perror("Error");
		return (-1);
	}

	for (i = 0; environ[i] != NULL; i++) 
    	{
		if (strncmp(vname, environ[i], strlen(vname)) == 0 && environ[i][strlen(vname)] == '=')
		{
			free(environ[i]);
			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];
			}
		}
	}

	return (0);
}
