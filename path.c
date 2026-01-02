#include "shell.h"

/**
 * get_path_env - Get PATH environment variable
 *
 * Return: PATH string or NULL
 */
char *get_path_env(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}

	return (NULL);
}

/**
 * check_path - Check if command exists in given path
 * @path_token: Directory path
 * @command: Command to find
 *
 * Return: Full path if found, NULL otherwise
 */
char *check_path(char *path_token, char *command)
{
	char *full_path;
	struct stat st;

	full_path = malloc(strlen(path_token) + strlen(command) + 2);
	if (!full_path)
		return (NULL);

	sprintf(full_path, "%s/%s", path_token, command);

	if (stat(full_path, &st) == 0)
		return (full_path);

	free(full_path);
	return (NULL);
}

/**
 * find_path - Find the full path of a command
 * @command: Command to find
 *
 * Return: Full path of command, or NULL if not found
 */
char *find_path(char *command)
{
	char *path_env, *path_copy, *path_token, *full_path;

	path_env = get_path_env();
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	path_token = strtok(path_copy, ":");

	while (path_token)
	{
		full_path = check_path(path_token, command);
		if (full_path)
		{
			free(path_copy);
			return (full_path);
		}
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}