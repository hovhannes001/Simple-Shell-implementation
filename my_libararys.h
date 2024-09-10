#ifndef HOVO
#define HOVO
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#define SIZE 500
#define HISTORY 1000
extern char* promt_name;
extern char** matrix;
void check(char *command);
void remove_newline(char *str);
#endif
