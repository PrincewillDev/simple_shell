#include "shell.h"

/**
 * check_del - function that checks if the char is delimter
 * @c: char that I want to check
 * @d: delimter
 * Return: 1 for true, 0 for false
 */
int check_del(char c, char *d)
{
	while (*d)
	{
		if (*d++ == c)
			return (1);
	}
	return (0);
}

/**
 * numWords - Function to know number of words
 * @str: line that I want to know number of words
 * @d: delimter
 * Return: the number of words
 */
int numWords(char *str, char *d)
{
	int i = 0, num = 0;

	for (; str[i]; i++)
	{
		if (!check_del(str[i], d) && (check_del(str[i + 1], d) || !str[i + 1]))
			num++;
	}
	return (num);
}

/**
 * strword - function to change string to words
 * @str: line that I want to divid it into words
 * @d: delimter
 * Retrun: Array of strings
 */
char **strword(char *str, char *d)
{
	int numTokens = 0, i = 0, j = 0;
	int numChar, tmp_i;
	char **Tokens;

	if (str == NULL)
		return (NULL);

	numTokens = numWords(str, d);
	if (numTokens == 0)
		return (NULL);

	Tokens = malloc(sizeof(char *) * (numTokens + 1));
	if (Tokens == NULL)
		return (NULL);

	for (i = 0, j = 0; j < numTokens; j++)
	{
		numChar = 0;
		while (check_del(str[i], d))
			i++;
		while (!check_del(str[i + numChar], d) && str[i + numChar])
			numChar++;
		Tokens[j] = malloc(sizeof(char) * (numChar + 1));
		if (Tokens[j] == NULL)
		{
			for (tmp_i = 0; tmp_i < j; tmp_i++)
				free(Tokens[tmp_i]);
			free(Tokens);
			return (NULL);
		}
		for (tmp_i = 0; tmp_i < numChar; tmp_i++)
			Tokens[j][tmp_i] = str[i++];
		Tokens[j][tmp_i] = '\0';
	}
	Tokens[j] = NULL;
	return (Tokens);
}
