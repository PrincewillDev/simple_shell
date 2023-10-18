#include "shell.h"

char *command_path(char *token);
/**
 * executing - function to excute programs
 * @arrStr: array of tokens
 * @environ: environment variable table
 */
void executing(char **arrStr, char **environ)
{
	char *tok;
	pid_t child_process;

	if (arrStr)
	{
		/* Get the full path of the command */
		tok = command_path(arrStr[0]);
		if (tok)
		{
			if (_strcmp(tok, "exit") == 0)
			{
				exit_func(arrStr);
				return;
			}
			if (_strcmp(tok, "setenv") == 0)
			{
				_setenv(arrStr[1], arrStr[2], 1);
				return;
			}
			if (_strcmp(tok, "unsetenv") == 0)
			{
				_unsetenv(arrStr[2]);
				return;
			}
			if (_strcmp(tok, "env") == 0)
			{
				_printenv(environ);
				return;
			}
			/* Create a child process to run the command */
			child_process = fork();
			if (child_process == 0)
			{
				/*Execute the command with arguments or path in the child process*/
				if (execve(tok, arrStr, environ) == -1)
				{
					perror("./hsh");
					exit(EXIT_FAILURE);
				}
			}
			else if (child_process == -1)
			{
				perror("Fork failed");
				exit(EXIT_FAILURE);
			}
			else
				wait(NULL);
		}
		else
			perror(getenv("PWD"));
		/*Free memory*/
		free(tok);
	}
}

/**
 * command_path - Function to know if the input is path or command
 * @token: the input from user
 * Return: the true path for command or path
 *         or NULL if there it's not command
 */
char *command_path(char *token)
{
	int i;
	char *path, *full_path;
	char *home_path = getenv("PATH");
	char *delimeter = ":";
	char **paths;

	/*Check if the home path is valid*/
	if (home_path == NULL || _strlen(home_path) == 0)
		return (NULL);

	/*Check if the command is already a full path*/
	for (i = 0; token[i]; i++)
	{
		if (token[i] == '/')
			return (token);
	}

	/*Parse the home path into an array of paths*/
	paths = strword(home_path, delimeter);

	/*Loop through the paths and append the command name*/
	for (i = 0; paths[i]; i++)
	{
		path = malloc(sizeof(char) * (_strlen(paths[i]) + _strlen(token) + 2));
		/*strcpy(path, paths[i]);*/
		/*path = strcat(paths[i], "/");*/
		/*path = strcat(path, token);*/

		if (path == NULL)
		{
			fprintf(stderr, "Memory allocation failed\n");
			exit(1);
		}
		strncpy(path, paths[i], _strlen(paths[i]) + 1);
		path[_strlen(paths[i])] = '/';
		path[_strlen(paths[i]) + 1] = '\0';
		full_path = _strcat(path, token);


		/*Check if the command exists in the current path*/
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(path);
	}

	/*Free memory*/
	free(paths);
	return (token);
}
