#include "shell.h"

/**
 * numTokens - function to know number of tokens
 * @str: string input
 * @d: delimiter
 * Return: number of tokenized strings
 */

int numTokens(char *str, char *d)
{
	int num = 0;
	char *tokenized;

	tokenized = strtok(str, d);
	while (tokenized)
	{
		num++;
tokenized = strtok(NULL, " ");
	}
	return (++num);
}

/**
 * parsingInput - function to parse input array and store it
 * @arroftok: array of strings to store tokeniezed
 * @str: string input
 * @d: delimiter
 */

void parsingInput(char **arroftok, char *str, char *d)
{
	int i = 0;
	char *tokenized;

	tokenized = strtok(str, d);
	while (tokenized)
	{
		arroftok[i] = malloc(sizeof(char) * strlen(tokenized));
		strcpy(arroftok[i], tokenized);
		tokenized = strtok(NULL, d);
		i++;
	}
	arroftok[i] = NULL;
}
