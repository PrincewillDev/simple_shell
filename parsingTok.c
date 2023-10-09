#include "shell.h"

/**
 * numTokens - function to know number of tokens
 * @str: string input
 * @d: delimiter
 * Return: number of tokenized strings
 */

int numTokens(const char *str, const char *d)
{
	int num = 0;
	char *tokenized;
	char *cpy_str;

	/*Copy the string to avoid modifying it*/
	cpy_str = strdup(str);

	/*Split the string by the delimiter and count the tokens*/
	tokenized = strtok(cpy_str, d);
	while (tokenized)
	{
		num++;
		tokenized = strtok(NULL, d);
	}

	/*Free memory*/
	free(cpy_str);
	return (num);
}

/**
 * parsingInput - function to parse input array and store it
 * @str: string input
 * @d: delimiter
 * Return: array of strings from parsing line
 */

char **parsingInput(char *str, char *d)
{
	char **arroftok = NULL;
	int i = 0;
	char *tokenized = NULL, *cpy_str;
	int n_tokens;

	/*Copy the string to avoid modifying it*/
	cpy_str = strdup(str);

	/*Count the number of tokens in the string*/
	n_tokens = numTokens(str, d);

	/*Allocate memory for the array of tokens*/
	arroftok = malloc(sizeof(char *) * (n_tokens + 1));

    /*Split the string by the delimiter and store the tokens in the array*/
	tokenized = strtok(cpy_str, d);
	while (tokenized)
	{
		arroftok[i] = strdup(tokenized);
		tokenized = strtok(NULL, d);
		i++;
	}
	arroftok[i] = NULL;

	/*Free memory*/
	free(cpy_str);

	return (arroftok);
}
