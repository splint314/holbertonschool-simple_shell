#include "shell.h"

/**
 * strtok_array_len - Takes a string as input and returns the array lenght.
 * @str: Input string.
 *
 * Return: The number of the lenght of the array to allocate.
 */
size_t strtok_array_len(char *str)
{
	char *str_cpy, *token;
	size_t arr_len;

	str_cpy = strdup(str);
	if (!str_cpy)
	{
		free(str);
		exit(1);
	}
	token = strtok(str_cpy, "\n ");
	arr_len = 1;
	while (token)
	{
		token = strtok(NULL, "\n ");
		arr_len++;
	}
	free(str_cpy);
	return (arr_len);
}

/**
 * array_strtok - Takes a string as input and returns an array.
 * @str: Input string.
 * Return: An array of strings.
 */
char **strtok_array(char *str)
{
	char *token;
	char **args;
	size_t i, arr_len;

	arr_len = strtok_array_len(str);
	if (arr_len == 1)
	{
		free(str);
		return (NULL);
	}
	args = malloc(sizeof(char *) * arr_len);
	if (!args)
	{
		free(str);
		exit(1);
	}
	token = strtok(str, "\n ");
	i = 0;
	while (token)
	{
		args[i] = malloc(strlen(token) + 1);
		if (!args[i])
		{
			while (i > 0)
			{
				i--;
				free(args[i]);
			}
			free(args);
			exit(1);
		}
		strcpy(args[i], token);
		token = strtok(NULL, "\n ");
		i++;
	}
	free(str);
	args[i] = NULL;
	return (args);
}
