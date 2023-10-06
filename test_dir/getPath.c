#include "shell.h"

/**
 * getPath - get the path of an executable
 * Return: pointer to mem allocated
 */

PathNode* getPath()
{
	char* pathVar = _getenv("PATH"), *token;
	PathNode *head = NULL; 
	PathNode *current = NULL;

	if (pathVar == NULL) {
		/* Handle the case where PATH is not set */
		return NULL;
	}

	token = strtok(pathVar, ":");
	while (token != NULL) {
		/* Create a new node for the directory */
		PathNode* newNode = (PathNode*)malloc(sizeof(PathNode));
		if (newNode == NULL) {
			/* Handle memory allocation error */
			return NULL;
		}

		/* Copy the directory path */
		newNode->directory = strdup(token);
		if (newNode->directory == NULL) {
			/* Handle memory allocation error */
			return NULL;
		}

		newNode->next = NULL;

		if (head == NULL) {
			/* If it's the first node, set it as the head */
			head = newNode;
			current = head;
		}
		else 
		{
			/* Otherwise, append it to the end of the list */
			current->next = newNode;
			current = newNode;
		}

		token = strtok(NULL, ":");
	}

	   while (current != NULL)
    {
        PathNode *temp = current;
        current = current -> next;
        free(temp);
    }

	return (head);
}
