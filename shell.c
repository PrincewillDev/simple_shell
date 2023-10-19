#include "shell.h"

/**
 * main - A command line interpreter
 * @argc: number of arguments
 * @argv: array of strings as arguments
 * @environ: environment variable table
 * Return: 0 on success
 */
extern char **environ;
int main(int argc, char **argv)
{
	char *linebuffer = NULL;
	size_t n = 0;
	ssize_t num_chars;
	char *delim = " \n";
	/*int n_tokens = 0;*/
	(void)argc;

	while (true)
        {
                /* Printing prompt and get input from user*/
                if (isatty(STDIN_FILENO))
                        print_prompt();
                num_chars = getline(&linebuffer, &n, stdin);
                /* Handling EOF or Ctrl D */
                if (num_chars == -1)
                        break;

                /*n_tokens = numWords(linebuffer, delim);*/
                /*Allocate memory for argv: This memory location for pointer to pointer */
                /*argv = malloc(sizeof(char *) * (n_tokens + 1));*/

                argv = NULL;

                if (linebuffer != NULL)
                {
                        /*n_tokens = numWords(linebuffer, delim);*/
                        argv = strword(linebuffer, delim);
                }

                /*argv = strword(linebuffer, delim);*/
                if (argv == NULL)
                {
                        perror("hsh: memory allocation failed");
                        free(linebuffer);
                        return (2);
                }
                /*Note: I think we can use linked list here*/
                executing(argv, environ);
                free(argv);
        }
        /*free memory*/
        free(linebuffer);
	return (0);
}
