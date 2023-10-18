#include "shell.h"

/**
 * printStr - function to print strings
 * @str: string to print
 */

void printStr(char *str)
{
	write(STDOUT_FILENO, str, strlen(str));
}

/**
 * print_prompt - function to print the prompt
 */

void print_prompt(void)
{
	printStr("(pcsh) $ ");
}

