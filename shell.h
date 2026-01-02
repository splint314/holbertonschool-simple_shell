#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

size_t strtok_array_len(char *str);
char **strtok_array(char *str);
char **path(char *args[], char **env);
void free_arr(char **args);
void fork_(char *args[], char **env);

#endif
