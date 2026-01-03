#include "shell.h"

/**
 * print_env - Print all environment variables
 *
 * Description: Prints each environment variable on a new line
 * in the format NAME=value
 *
 * Return: void
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}