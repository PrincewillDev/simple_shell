#include "shell.h"

/**
 * *_strcpy - copies the string pointed to by src, including \0.
 *@src: pointer.
 *@dest: pointer.
 *Return: the pointer to dest.
 */

char *_strcpy(char *dest, char *src)
{
	int i, length;

	for (length = 0; src[length] != '\0'; length++)
	{
	}

	for (i = 0; i <= length ; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * _strdup - This function duplicate a string in new memory.
 * @str: This is a string pointer
 * Return: returns a pointer to malloc
 */

char *_strdup(char *str)
{

	int i, len = 0;

	char *sptr;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	sptr = (char *) malloc(len * sizeof(char) + 1);
	if (sptr == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		sptr[i] = str[i];
	}
	sptr[i++] = '\0';

	return (sptr);
}


/**
 * _strlen - calculates for the lenght of a string
 *
 * @s: The function parameter
 *
 * Return: Always 0 (Success)
 *
 */

int _strlen(const char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;

	return (len);
}


/**
 * _strncmp - Compares first n bytes of a string to another
 * @s1: First string
 * @s2: Second string
 * @n: Number of bytes/characters to compare
 * Return: 0 if strings are same, non-zero if not
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i = 0;

	/* Compare each element of s1 with s2 */
	for (i = 0; (s1[i] != '\0' || s2[i] != '\0') && i < n; i++)
	{
		/* Return 0 if s1 and s2 are the same */
		if (s1[i] == s2[i])
		{
			if (s1[i + 1] == '\0' || s2[i + 1] == '\0' || i + 1 == n)
				return (0);
		}
		else if (s1[i] < s2[i] || s2[i] < s1[i])
			break;
	}
	/* Return differene bwtween strings if they aren't same */
	return (s1[i] - s2[i]);
}
