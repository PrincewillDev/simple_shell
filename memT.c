#include "shell.h"

/**
 * free_tracked_memory - Frees tracked dynamically allocated pointers
 *
 * Return: void
 */
void freetrackedmem(void)
{
	int i;

	for (i = 0; i < tSize; i++)
	{
		if (memtracker[i] != NULL)
			free(memtracker[i]);
	}
	if (memorytracker != NULL)
		free(memorytracker);
}

/**
 * free_tracked_memory_alias - Frees alias_s linked list
 * Return: void
 */
void freetrackedmemalias(void)
{
	alias_s *ptr = head;
	alias_s *next;

	while (ptr != NULL)
	{
		free(ptr->name);
		free(ptr->value);
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	head = NULL;
}
