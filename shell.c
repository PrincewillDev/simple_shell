#include "shell.h"

/**
 * main - A command line interpreter
 * @argc: number of arguments
 * @argv: array of strings as arguments
 * @environ: environment variable table
 * Return: 0 on success
 */

int main(int argc, char **argv, char **environ)
{
	char *linebuffer;
	size_t n = 0;
	ssize_t num_chars;
	char *delim = " \n";
	int n_tokens = 0;
	(void)argc;

	while (true)
	{
		/* Printing prompt and get input from user*/
		if (isatty(STDIN_FILENO))
		{
			print_prompt();
		}
		num_chars = getline(&linebuffer, &n, stdin);
		/* Handling EOF or Ctrl D */
		if (num_chars == -1)
		{	
			printStr("\n");
			break;
		}

		n_tokens = numWords(linebuffer, delim);
		/*Allocate memory for argv: This memory location for pointer to pointer */
		argv = malloc(sizeof(char *) * (n_tokens + 1));
		if (argv == NULL)
		{
			perror("hsh: memory allocation failed");
			return (2);
		}
		/*Note: I think we can use linked list here*/
		argv = strword(linebuffer, delim);
		executing(argv, environ);
		free(argv);
	}
	/*free memory*/
	free(linebuffer);
	return (0);
}
