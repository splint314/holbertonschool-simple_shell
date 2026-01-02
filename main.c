#include "shell.h"

/**
 * main - Shell Function. Takes commands as input and execute the programs
 * linked to these commands.
 * @ac: Number of arguments provided (Void)
 * @av: Array with the arguments provided (Void)
 * @env: Environment to pass into the childrenn processes.
 * Return: 1 on error. 0 on success.
 */
int main(int ac, char **av, char **env)
{
	size_t len;
	ssize_t nread;
	char *str;
	char **args;
	(void)av;
	(void)ac;

	while (1)
	{
		str = NULL;
		nread = getline(&str, &len, stdin);
		if (nread == -1)
			break;
		args = strtok_array(str);
		if (!args)
			continue;
		fork_(args, env);
		free_arr(args);
	}
	free(str);
	return (0);
}
