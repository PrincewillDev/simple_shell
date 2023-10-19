#include "shell.h"

/**
 * _setenv - Sets a new value for an environment variable
 * @var: Environment variable name
 * @value: Environment variable value
 * @overwrite: Integer flag to overwrite or not
 * Return: 1 on success, -1 on failure
 */

int tSize = 0;
char *memtracker[100] = {NULL};
char **memorytracker = NULL;

int _setenv(char *var, char *value, int overwrite)
{
	int varLen = _strlen(var), valLen = _strlen(value), i, j;
	int envstrLen = varLen + valLen + 2;
	char *newVariable = NULL, **envNew;

	for (i = 0; environ[i] != NULL; i++)
	{
		/* If environment variable exists */
		if (_strncmp(var, environ[i], varLen) == 0)
		{
			if (overwrite == 0)
				return (0);
			environ[i] = malloc(sizeof(char) * envstrLen);
			if (environ[i] == NULL)
			{
				perror("hsh: _setenv: ");
				return (-1);
			}
			/* Store allocated memory in tracker string */
			memtracker[tSize] = environ[i];
			tSize++;

			_strcpy(environ[i], var);
			_strcat(environ[i], "=");
			_strcat(environ[i], value);
			return (0);
		}

		/* If environment variable does not exist */
		if ((environ[i + 1] == NULL) && (_strncmp(var, environ[i], varLen) != 0))
		{
			if (overwrite == 0)
				return (0);
			/* Build new environment variable array */
			envNew = malloc(sizeof(char *) * (i + 3));
			if (envNew == NULL)
			{
				perror("hsh: _setenv: ");
				return (-1);
			}
			memorytracker = envNew;
			/* Copy old environment variables into new env array */
			for (j = 0; environ[j] != NULL; j++)
				envNew[j] = environ[j];
			/* Construct new environment variable string */
			newVariable = malloc(sizeof(char) * envstrLen);
			if (newVariable == NULL)
			{
				printf("shell: _setenv: Memory allocation error\n");
				return (-1);
			}
			memtracker[tSize] = newVariable;
			tSize++;

			_strcpy(newVariable, var);
			_strcat(newVariable, "=");
			_strcat(newVariable, value);
			envNew[j++] = newVariable;
			envNew[j++] = NULL;

			environ = NULL;
			environ = envNew;
			return (0);
		}
	}
	return (-1);
}

/**
 * _printenv - Prints environment variables of a program
 * Return: 0 if success, -1 on fail
 */

int _printenv(void)
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


/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of environment variable
 * Return: Pointer to the value of the environment variable
 */
char *_getenv(const char *name)
{
	int i = 0, size;

	if (name == NULL)
	{
		perror("hsh: ");
		return (NULL);
	}
	size = _strlen(name);
	while (environ[i] != NULL)
	{
		if (_strncmp(name, environ[i], size) == 0)
			return (environ[i] + size + 1);
		i++;
	}
	return (NULL);
}
