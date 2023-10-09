#include "shell.h"

/**
 * parsing_input - function to parse input
 * @tokenized: string that I will store tokenized str
 * @str: string input
 * @delim: delemiter
*/

int parsing_input(char *tokenized, char *str, char *delim)
{
    int num = 0;

    tokenized = strtok(str, delim);
    while (tokenized)
    {
        num++;
        tokenized = strtok(NULL, " ");
    }
    return (++num);
}