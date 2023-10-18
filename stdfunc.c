#include "shell.h"

/**
 * Description: _atoi - Converts a string to an integer.
 * @s: Character string to be converted to an integer.
 * Return: 0 if success.
 */

int _atoi(char *s)
{
	int i = 0;
	unsigned int integer = 0;/* unsigned int to hold larger int values */

	/* Check for sign */
	if (s[0] == '-')
		return (-1);

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			/* Converts the current char to ASCII */
			integer = integer * 10 + (s[i] - '0');
			i++;
		}
		else
			return (-1);
	}

	return (integer);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * Description: _strcat - Concatenates two strings.
 * @dest: destination string
 * @src: source string
 * Return: Pointer to destination string.
 */

char *_strcat(char *dest, char *src)
{
	/* Initiate a loop counter for adding src elements to dest */
	int i;

	/* Calculate length of src and dest string */
	int length = 0;

	while (dest[length] != '\0')
	{
		length++;
	}

	/* Add src elements to end of dest */
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[length + i] = src[i];
	}

	/* Add null character to end of dest string */
	dest[length + i] = '\0';

	return (dest);
}

/**
 * Description: _strchr - Locates a character in a string.
 * @c: Character to be located
 * @s: String to be checked.
 * Return: Pointer to first occurence of c or null
 */

char *_strchr(char *s, char c)
{
	int i = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
		{
			return (&s[i]);
		}
	}

	return (NULL);
}

/**
 * _strcmp - Compares two strings
 * @s1: Pointer to the first string to be compared
 * @s2: Pointer to the second string to be compared
 *
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 */

int _strcmp(char *s1, char *s2)
{

	while (*s1 != '\0' && *s2 != '\0')

	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}
