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
	char *path_cpy;
	char *_path;

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path_cpy = strdup(env[i] + 5);
			if (!path_cpy)
				exit(1);

			token = strtok(path_cpy, ":");
			while (token)
			{
				_path = malloc(strlen(token) + strlen(args[0]) + 2);
				if (!_path)
					exit(1);

				sprintf(_path, "%s/%s", token, args[0]);
				if (access(_path, X_OK) == 0)
				{
					free(args[0]);
					args[0] = _path;
					free(path_cpy);
					return (args);
				}

				free(_path);
				token = strtok(NULL, ":");
			}
			free(path_cpy);
		}
		i++;
	}
	return (NULL);
}
