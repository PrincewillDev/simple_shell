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
