#include "shell.h"


/**
 * find_alias - Checks the alias linked list for a match
 * @cmd_name: Command to check for in alias list
 * Return: Pointer to alias value or NULL
 */
char *find_alias(char *cmd_name)
{
	alias_s *ptr = head;

	while (ptr != NULL)
	{
		if (_strcmp(ptr->name, cmd_name) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}

	return (NULL);
}

/**
 * print_alias - Prints an alias
 * @name: Name of alias
 * Return: 0 on success, -1 on fail
 */

alias_s *head;
void print_alias(char *name)
{
	alias_s *ptr = head;

	while (ptr != NULL)
	{
		if (_strcmp(ptr->name, name) == 0)
			_printf("%s='%s'\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}

/**
 * print_all_aliases - Prints all aliases
 *
 * Return: Number of aliases printed
 */
void print_all_aliases(void)
{
	alias_s *ptr = head;
	int i = 0;

	while (ptr != NULL)
	{
		_printf("%s='%s'\n", ptr->name, ptr->value);
		ptr = ptr->next;
		i++;
	}
}

/**
 * add_alias - Adds new alias to alias struct
 * @aliasStr: String containing alias name and value
 * Return: 0 if succes, -1 on fail
 */
alias_s *add_alias(char *aliasStr)
{
	alias_s *new, *p = head;
	char *name, *value, *alias_strcp = _strdup(aliasStr);
	char delim[] = "=";


	/* Split alias string int name and value */
	name = strtok(alias_strcp, delim);
	value = strtok(NULL, delim);

	/* Check if alias exists */
	while (p != NULL)
	{
		if (_strcmp(p->name, name) == 0)
		{
			free(p->value);
			p->value = _strdup(value);
			free(alias_strcp);
			return (p);
		}
		p = p->next;
	}

	/* Allocate memory for new alias */
	new = malloc(sizeof(alias_s));
	if (new == NULL)
	{
		free(alias_strcp);
		return (NULL);
	}

	/* Initialize new alias */
	new->name = _strdup(name);
	new->value = _strdup(value);
	new->next = NULL;

	free(alias_strcp);
	alias_strcp = NULL;

	/* If alias list is empty */
	if (head == NULL)
	{
		head = new;
		return (new);
	}

	/* If alias list exists */
	p = head;
	while (p->next != NULL)
		p = p->next;
	p->next = new;
	return (new);
}

/**
 * alias_handler - Handles alias commands
 * @argv: Argument vector
 * Return: void
 */
void alias_handler(char **argv)
{
	int i;

	/* If alias has no arguments */
	if (argv[1] == NULL)
	{
		print_all_aliases();
		return;
	}
	/* If alias has two arguments */
	else if (argv[2] == NULL)
	{
		if (_strchr(argv[1], '=') == NULL)
		{
			print_alias(argv[1]);
			return;
		}
		else
		{
			add_alias(argv[1]);
			return;
		}
	}
	/* If has more than two arguments */
	else
	{
		for (i = 0; argv[i] != NULL; i++)
		{
			if (_strchr(argv[i], '=') == NULL)
			{
				print_alias(argv[i]);
			}
			else
			{
				add_alias(argv[i]);
			}
		}
		return;
	}
	return;
}
