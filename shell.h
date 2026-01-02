#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

/* shell loop */
void shell_loop(void);

/* split lines into arguments*/
char **split_line(char *line);

/* execution */
void execute_command(char *command);

/* path */
char *resolve_path(char *command);

/* utils */
char *read_line(void);

#endif
