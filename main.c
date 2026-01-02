#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0
 */
int main(int ac, char **av)
{
	(void)ac;

	shell_loop(av[0]);
	return (0);
}
