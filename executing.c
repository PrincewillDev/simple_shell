#include "shell.h"

char *command_path(char *token);
/**
 * executing - function to excute programs
 * @arrStr: array of tokens
 */

void executing(char **arrStr)
{
	char *tok = NULL;
	pid_t child_process;

	if (arrStr)
	{
		/* Get the full path of the command */
		tok = command_path(arrStr[0]);
		if (tok)
		{
			if (strcmp(tok, "exit") == 0)
			{
				exit_func(arrStr);
				return;
			}
			/* Create a child process to run the command */
			child_process = fork();
			if (child_process == 0)
			{
				/*Execute the command with arguments or path in the child process*/
				if (execve(tok, arrStr, NULL) == -1)
				{
					perror(getenv("PWD"));
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
	char *path, *path_cpy;
	char *home_path = getenv("PATH");
	char *delimeter = ":";
	char **paths = NULL;

	/*Check if the home path is valid*/
	if (home_path == NULL || strlen(home_path) == 0)
		return (NULL);

	if (strcmp(token, "exit") == 0)
		return (token);

	/*Check if the command is already a full path*/
	for (i = 0; token[i]; i++)
	{
		if (token[i] == '/')
			return (token);
	}

	/*Copy the home path to avoid modifying it*/
	path_cpy = strdup(home_path);

	/*Parse the home path into an array of paths*/
	paths = parsingInput(path_cpy, delimeter);

	/*Loop through the paths and append the command name*/
	for (i = 0; paths[i]; i++)
	{
		path = strdup(paths[i]);
		path = strcat(paths[i], "/");
		path = strcat(path, token);

		/*Check if the command exists in the current path*/
		if (access(path, F_OK) == 0)
		{
			/*Free memory*/
			free(path_cpy);
			free(paths);
			return (path);
		}
		free(path);
	}

	/*Free memory*/
	free(path_cpy);
	free(paths);

	return (NULL);
}
