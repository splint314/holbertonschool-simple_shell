#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/* shell loop */
void shell_loop(void);

/* execution */
void execute_command(char *command);

/* path */
char *resolve_path(char *command);

/* utils */
char *read_line(void);
void print_error(char *name, char *command);

#endif
