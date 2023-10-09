#ifndef SHELL_H
#define SHELL_H

/***********Libraries***********/
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

/***********Functions***********/
/*Function to print string with write*/
void printStr(char *str);
void print_prompt(void);
int getuserInput(void);

/*Parsing Functions*/
int numTokens(const char *str, const char *d);
char **parsingInput(char *str, char *d);

/*Executing Functions*/
void executing(char **arrof_str);

/*Built-in functions*/
void exit_func(char **tok);

#endif /* SHELL_H */
