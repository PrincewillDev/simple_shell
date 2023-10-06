#ifndef SHELL_H
#define SHELL_H

/* Path struct */
struct PathNode {
	char* directory;
	struct PathNode* next;
};

typedef struct PathNode PathNode;

/***********Libraries***********/
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

/***********Functions***********/
/*Function to print string with write*/
void printStr(char *str);
void print_prompt(void);
int getuserInput(void);

/*Parsing Functions*/
int numTokens(char *str, char *d);
void parsingInput(char **arroftok, char *str, char *d);

/*Executing Functions*/
/*void executing(char **arrof_str);*/
void executing(char **arrof_str, char **envp);

/*Get path functions*/
char *_getenv(const char *name);
PathNode* getPath();
char *pathdir(char *pathptr);


#endif /* SHELL_H */

