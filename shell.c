#include "shell.h"

/**
 * main - A command line interpreter
 * @argc: number of arguments
 * @argv: array of strings as arguments
 * Return: 0 on success
 */

int main(int argc, char **argv)
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
		{
			printf("Exiting ^_^\n"); /* Testing */
			return (-1);
		}
		/* Tokenizing the inputs from the user */
		cpy_linebuffer = malloc(sizeof(char) * num_chars);
		if (cpy_linebuffer == NULL)
		{
			perror("hsh: memory allocation failed");
			return (1);
		}
		strcpy(cpy_linebuffer, linebuffer);
		/* Number of tokens */
		n_tokens = numTokens(linebuffer, delim);
		/*Allocate memory for argv: This memory location for pointer to pointer */
		argv = malloc(sizeof(char *) * n_tokens);
		/*Note: I think we can use linked list here*/
		parsingInput(argv, cpy_linebuffer, delim);
		executing(argv, NULL);
	}
	/*free memory*/
	free(argv);
	free(linebuffer);
	free(cpy_linebuffer);
	return (0);
}
