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
	char *linebuffer = NULL, *cpy_linebuffer = NULL;
	size_t n = 0;
	ssize_t num_chars;
	char *delim = " \n";
	int n_tokens = 0;
	(void)argc;

	while (true)
	{
		/* Printing prompt and get input from user*/
		print_prompt();
		num_chars = getline(&linebuffer, &n, stdin);
		/* Handling EOF or Ctrl D */
		if (num_chars == -1)
		{	printStr("\n");
			break;
		}
		/* cpy_linebuffer appears to be not useful in this program and should be removed is not useful */
		cpy_linebuffer = strdup(linebuffer);
		n_tokens = numTokens(linebuffer, delim);
		/*Allocate memory for argv: This memory location for pointer to pointer */
		argv = malloc(sizeof(char *) * n_tokens);
		if (argv == NULL)
		{
			perror("hsh: memory allocation failed");
			return (1);
		}
		/*Note: I think we can use linked list here*/
		argv = parsingInput(linebuffer, delim);
		executing(argv, environ);
		free(argv);
	}
	/*free memory*/
	free(cpy_linebuffer);
	free(linebuffer);
	return (0);
}
