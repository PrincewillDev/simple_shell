#include "shell.h"
/* Function to execute a command from a specific file */
void executing(char **arrof_str, char **envp)
{
    pid_t child_process = fork();

    if (child_process == 0)
    {
        if (arrof_str[0][0] == '/')
        {
            if (execve(arrof_str[0], arrof_str, envp) == -1)
                {
                    perror("execve failed");
                    exit(EXIT_FAILURE);
                }

        }
        else 
        {

        
            char *command = arrof_str[0]; /* The first argument is the command */
            char *fullPath = _getenv("PATH"); /* Get the PATH environment variable */
            char *path;
            int found = 0;

            /* Tokenize the PATH into individual directories */
            char *token = strtok(fullPath, ":");
            while (token != NULL)
            {
                /* Construct the full path to the executable */
                path = (char *)malloc(strlen(token) + strlen(command) + 2);
                if (path == NULL)
                {
                    perror("malloc failed");
                    exit(EXIT_FAILURE);
                }
                strcpy(path, token);
                strcat(path, "/");
                strcat(path, command);

                /* Check if the file exists and is executable */
                if (access(path, X_OK) == 0)
                {
                    found = 1;
                    break;
                }

                free(path);
                token = strtok(NULL, ":");
            }

            if (found)
            {
                if (execve(path, arrof_str, envp) == -1)
                {
                    perror("execve failed");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                /*%s: command not found\n", command*/
                perror("./hsh");
                exit(EXIT_FAILURE);
            }
        }
    }
    else if (child_process == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
}