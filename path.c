#include "shell.h"

/**
 * path - Resolves command path using PATH
 * @args: Command arguments
 * @env: Environment variables
 *
 * Return: args if path found or NULL if not
 */
char **path(char *args[], char **env)
{
	char *path_var = NULL, *path_copy, *dir, *full;
	size_t i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			path_var = env[i] + 5;
		i++;
	}

	if (!path_var || path_var[0] == '\0')
		return (NULL);

	path_copy = strdup(path_var);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full = malloc(strlen(dir) + strlen(args[0]) + 2);
		if (!full)
			break;

		sprintf(full, "%s/%s", dir, args[0]);
		if (access(full, X_OK) == 0)
		{
			free(args[0]);
			args[0] = full;
			free(path_copy);
			return (args);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
