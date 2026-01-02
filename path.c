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
	char *path_env = NULL;
	char *token, *full_path;

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = strdup(env[i] + 5);
			break;
		}
		i++;
	}
	if (!path_env)
		return (NULL);

	token = strtok(path_env, ":");
	while (token)
	{
		full_path = malloc(strlen(token) + strlen(args[0]) + 2);
		if (!full_path)
		{
			free(path_env);
			exit(1);
		}
		sprintf(full_path, "%s/%s", token, args[0]);
		if (access(full_path, X_OK) == 0)
		{
			free(args[0]);
			args[0] = full_path;
			free(path_env);
			return (args);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_env);
	return (NULL);
}
