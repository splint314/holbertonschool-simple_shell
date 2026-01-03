#include "shell.h"

/**
 * strtok_array_len - Computes number of tokens in a string
 * @str: Input string
 *
 * Return: Number of tokens + 1 (NULL)
 */
size_t strtok_array_len(char *str)
{
	char *copy, *token;
	size_t count = 0;

	copy = strdup(str);
	if (!copy)
		return (0);

	token = strtok(copy, " \n");
	while (token)
	{
		count++;
		token = strtok(NULL, " \n");
	}
	free(copy);
	return (count + 1);
}

/**
 * strtok_array - Split string into token
 * @str: Input string.
 * Return: NULL, terminated array of strigs
 */
char **strtok_array(char *str)
{
	char **args;
	char *token;
	size_t i = 0, len;

	len = strtok_array_len(str);
	if (len < 2)
		return (NULL);

	args = malloc(sizeof(char *) * len);
	if (!args)
		return (NULL);

	token = strtok(str, " \n");
	while (token)
	{
		args[i] = strdup(token);
		if (!args[i])
			return (NULL);
		i++;
		token = strtok(NULL, " \n");
	}
	args[i] = NULL;
	return (args);
}
