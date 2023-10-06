#include "shell.h"

char *pathdir(char *pathptr)
{
    PathNode *path = getPath(), *current;
    char *fullpath;
    for (current = path; current != NULL; current = current->next)
    {
       fullpath = malloc(strlen(current->directory) + strlen(pathptr) + 2);
        strcpy(fullpath, current->directory);
        strcat(fullpath, "/");
        strcat(fullpath, pathptr);
        if (access(fullpath, F_OK) == 0)
        {
            /*File exist*/
            return(fullpath);
        }
        free(fullpath);
    }

    return (NULL);
}


#include "shell.h"

/**
 * executing - function to excute programs
 * @arrof_str: array of tokens
 */

void executing(char **arrof_str)
{
	char *tok = NULL;
	pid_t child_process = fork();

	if (arrof_str)
	{
		tok = arrof_str[0];
		if (child_process == 0)
		{
			if (execve(tok, arrof_str, NULL) == -1)
				perror("./hsh");
			exit(EXIT_FAILURE);
		}
		else if (child_process == -1)
			exit(EXIT_FAILURE);
		else
			wait(NULL);
	}
}
