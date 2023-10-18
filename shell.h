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


extern char **environ;

/***********Functions***********/
/*Function to print string with write*/
void printStr(char *str);
void print_prompt(void);
int getuserInput(void);

/*Parsing and helpers Functions*/
int check_del(char c, char *d);
int numWords(char *str, char *d);
char **strword(char *str, char *d);

/*Executing Functions*/
void executing(char **arrof_str, char **environ);

/*Built-in functions*/
void exit_func(char **tok);
int _printenv(char **tok);
int _setenv(const char *vname, const char *value, int overwrite);
int _unsetenv(const char *vname);

/* Custom functions prototype */
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, int n);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);
int _atoi(char *s);


#endif /* SHELL_H */
