#include "shell.h"

char *linebuffer = NULL;
int status = 0;

/**
 * signal_handler - Handles the Ctrl+C signal
 * @sig: Signal
 * Return: void
 */
void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		_putchar('\n');
		free(linebuffer);
		freetrackedmem();
		exit(EXIT_SUCCESS);
	}
}

/**
 * which - Returns the full path of a command
 * @cmd_name: Command
 * Return: Command path on success, NULL if command is not found
 */
char *which(char *cmd_name)
{
	struct stat fileStat;
	char *cmdpath = NULL, *dir, *path = _getenv("PATH"), *pathcpy = NULL, c = '/';
	const char delim[] = ":\n";
	int cmdpathLen;

	/* Check for command in alias struct */
	if (find_alias(cmd_name) != NULL)
		cmd_name = find_alias(cmd_name);

	/* Handle path command */
	if ((_strchr(cmd_name, c)) != NULL)
	{
		/* Check if command is in PATH */
		if (stat(cmd_name, &fileStat) == 0)
		{
			/* Check if file is executable */
			if (access(cmd_name, X_OK) == 0)
				return (_strdup(cmd_name));
			else
				return (NULL);
		}
		else
			return (NULL);
	}

	/* Handle command name */
	pathcpy = _strdup(path);
	if (pathcpy == NULL)
	{
		return (NULL);
	}
	dir = strtok(pathcpy, delim);
	while (dir)
	{
		cmdpathLen = _strlen(dir) + _strlen(cmd_name) + 2;
		cmdpath = malloc(sizeof(char) * cmdpathLen);
		if (cmdpath == NULL)
		{
			perror("hsh: ");
			free(pathcpy);
			pathcpy = NULL;
			return (NULL);
		}
		_strcpy(cmdpath, dir);
		_strcat(cmdpath, "/");
		_strcat(cmdpath, cmd_name);
		/* Check if path is valid */
		if (stat(cmdpath, &fileStat) == 0)
		{
			free(pathcpy);
			pathcpy = NULL;
			if (access(cmdpath, X_OK) == 0)
				return (cmdpath);
			free(cmdpath);
			cmdpath = NULL;
		}
		free(cmdpath);
		cmdpath = NULL;
		dir = strtok(NULL, delim);
	}
	free(pathcpy);
	if (cmdpath)
	{
		free(cmdpath);
		cmdpath = NULL;
	}
	return (NULL);
}

/**
 * main - A command line interpreter
 * Return: 0 on success
 */
int main(void)
{
	int argc, num_chars;
	char **argv = NULL;
	char *executable = NULL, *oldpwd = NULL, *newpwd = NULL;
	char *com_removal;
	size_t linesize = 0;
	pid_t pid;
	struct stat dir_stat;

	/* Set environment variables */

	while (1)
	{
		/* Implement signal handler */
		signal(SIGINT, signal_handler);

		if (isatty(STDIN_FILENO) == 1)
		{
			/* Interactive mode */
			write(STDIN_FILENO, "(pcsh) $  ", 9);
			if (linebuffer != NULL)
				free(linebuffer);
			linebuffer = NULL;
			linesize = 0;
			num_chars = getline(&linebuffer, &linesize, stdin);
			if (num_chars == -1)
			{
				if (feof(stdin))
				{
					_putchar('\n');
					break;
				}
				perror("hsh: ");
				continue;
			}
			else if (num_chars == 1)
				continue;
		}
		else
		{
			/* Non-interactive mode */
			linebuffer = readcmdfile();
		}

		if (linebuffer == NULL)
			break;
		/* Handle comments */
		com_removal = _strchr(linebuffer, '#');
		if (com_removal != NULL)
			*com_removal = '\0';

		/* Build argv */
		argc = linetoargs(&linebuffer, &argv);
		if (argc == -1 || argv == NULL)
		{
			free(linebuffer);
			linebuffer = NULL;
			continue;
		}
		/* Check for variable replacement */
		variable_replace(&argv);
		/* Check for alias */
		if (_strcmp(argv[0], "alias") == 0)
		{
			alias_handler(argv);
			free(linebuffer);
			linebuffer = NULL;
			free_args(&argv);
			continue;
		}
		/* Check if command is == exit */
		if (_strcmp(argv[0], "exit") == 0)
		{
			if (argv[1])
			{
				status = _atoi(argv[1]);
				if (status == -1)
				{
					custom_perror_builtin("exit", argv[1]);
					status = 2;
				}
			}
			break;
		}
		/* Check if command is == env */
		if (_strcmp(argv[0], "env") == 0)
		{
			if (_printenv() == -1)
				status = 2;
			free(linebuffer);
			linebuffer = NULL;
			free_args(&argv);
			continue;
		}
		if (_strcmp(argv[0], "setenv") == 0)
		{
			if (argv[1] != NULL && argv[2] != NULL)
				_setenv(argv[1], argv[2], 1);
			free_args(&argv);
			free(linebuffer);
			linebuffer = NULL;
			continue;
		}
		if (_strcmp(argv[0], "unsetenv") == 0)
		{
			if (argv[1] != NULL)
				_unsetenv(argv[1]);
			free_args(&argv);
			free(linebuffer);
			linebuffer = NULL;
			continue;
		}
		/* Check for cd */
		if (_strcmp(argv[0], "cd") == 0)
		{
			if (argv[1] == NULL)
			{
				if (_getenv("HOME") != NULL)
				{
					oldpwd = _strdup(_getenv("PWD"));
					if (_getenv("HOME") != NULL)
						chdir(_getenv("HOME"));
				}
			}
			else if (_strcmp(argv[1], "-") == 0)
			{
				if (_getenv("OLDPWD") != NULL)
				{
					oldpwd = _strdup(_getenv("PWD"));
					chdir(_getenv("OLDPWD"));
					newpwd = getcwd(NULL, 0);
					_printf("%s\n", newpwd);
					free(newpwd);
					newpwd = NULL;
				}
				else
					_printf("%s\n", _getenv("PWD"));
			}
			else if (argv[1])
			{
				if (stat(argv[1], &dir_stat) == 0)
				{
					oldpwd = _strdup(_getenv("PWD"));
					chdir(argv[1]);
				}
				else
				{
					custom_perror_builtin("cd", argv[1]);
					status = 2;
				}
			}
			newpwd = getcwd(NULL, 0);
			if (newpwd == NULL)
			{
				if (oldpwd != NULL)
					free(oldpwd);
				oldpwd = NULL;
			}
			else
			{
				if (oldpwd != NULL)
				{
					_setenv("OLDPWD", oldpwd, 1);
					free(oldpwd);
					oldpwd = NULL;
				}
				_setenv("PWD", newpwd, 1);
				free(newpwd);
				newpwd = NULL;
			}
			free(linebuffer);
			linebuffer = NULL;
			free_args(&argv);
			continue;
		}
		/* Check if program is a current directory executable */
		if (_strncmp("./", argv[0], 2) == 0)
		{
			if (access(argv[0], F_OK | X_OK) == 0)
			{
				executable = _strdup(argv[0]);
			}
			else
			{
				custom_perror(argv[0]);
				status = 2;
				free(linebuffer);
				linebuffer = NULL;
				free_args(&argv);
				continue;
			}
		}
		else
		{
			executable = which(argv[0]);
			if (executable == NULL)
			{
				errno = ENOENT;
				custom_perror(argv[0]);
				status = 127;
				free(linebuffer);
				linebuffer = NULL;
				free_args(&argv);
				continue;
			}
		}

		/* Create new process */
		pid = fork();
		if (pid == -1)
		{
			perror("hsh: ");
			free(linebuffer);
			linebuffer = NULL;
			free_args(&argv);
			if (executable)
			{
				free(executable);
				executable = NULL;
			}
			continue;
		}
		if (pid == 0)
		{
			execve(executable, argv, environ);
			if (_strcmp(executable, "cd"))
				custom_perror_builtin(executable, argv[1]);
			else
				perror("hsh: ");
			exit(2);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			free(linebuffer);
			linebuffer = NULL;
			free_args(&argv);
			free(executable);
			executable = NULL;
		}
	}
	if (argv)
		free_args(&argv);
	if (linebuffer)
	{
		free(linebuffer);
		linebuffer = NULL;
	}
	linesize = 0;
	if (executable)
		free(executable);
	freetrackedmem();
	freetrackedmemalias();
	return (status);
}
