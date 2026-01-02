#include "shell.h"

/**
 * path - Function that finds the path of a command.
 * @args: Array of command and arguments.
 * @env: Environment variables.
 * Return: path of the command, or NULL.
 */
char **path(char *args[], char **env)
{
	size_t i = 0;
	char *token;
	char *_path;
	char *path_cpy;

	while (env[i])
	{
		if (strncmp(env[i], "PATH", 4) == 0)
		{
			path_cpy = malloc(sizeof(char) * (strlen(env[i]) + 1));
			strcpy(path_cpy, env[i]);
			token = strtok(path_cpy, "=");
			token = strtok(NULL, ":");
			while (token)
			{
				_path = malloc(sizeof(char) * (strlen(token) + strlen(args[0]) + 2));
				sprintf(_path, "%s/%s", token, args[0]);
				if (access(_path, X_OK) == 0)
				{
					free(args[0]);
					args[0] = malloc(strlen(_path) + 1);
					strcpy(args[0], _path);
					free(_path);
					free(path_cpy);
					return (args);
				}
				token = strtok(NULL, ":");
				free(_path);
			}
			free(path_cpy);
		}
		i++;
	}
	return (NULL);
}
