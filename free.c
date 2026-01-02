#include "shell.h"

/**
 * free_arr - Function that frees a array of strings.
 * @args: array of strings to be free.
 */
void free_arr(char **args)
{
	size_t i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
