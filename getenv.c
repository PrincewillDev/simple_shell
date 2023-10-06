#include "shell.h"

/**
 * _getenv - get the environment variable
 * @name: name of the env var to get
 * Return: variable value on success
 */
char *_getenv(const char *name)
{
	extern char** environ;
	char *varName, *varValue;
	char** env;
	char* equalPosition;

	for(env = environ; *env != NULL; env++)
	{
		equalPosition = strchr(*env, '=');

		if (equalPosition != NULL)
		{
			*equalPosition = '\0';
			varName = *env;
			varValue = equalPosition + 1;
        

			if (strcmp(varName, name) == 0)
			{
				return (varValue);
			}
		}
	}

	return (NULL);
}