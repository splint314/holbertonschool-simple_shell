#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* Macros */
#define BUFFER_SIZE 1024

/* Global variables */
extern char **environ;

/* Function prototypes */
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args, char *argv0, int *count);
char *find_path(char *command);
void print_error(char *argv0, int count, char *command);
void print_env(void);

#endif /* SHELL_H */
