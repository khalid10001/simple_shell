#include "shell.h"

/**
 * exitShell - Exit the shell based on the given exit status.
 * @args: Arguments passed to the exit command.
 * @line: Input line from the user.
 * @exitCode: Exit code for the shell.
 * Return: None
 */
void exitShell(char **args, char *line, int exitCode)
{
	int exitStatus = 0;

	if (!args[1])
	{
		free(line);
		free(args);
		exit(exitCode);
	}

	exitStatus = atoi(args[1]);

	free(line);
	free(args);
	exit(exitStatus);
}

/**
 * printEnvironment - Print all environment variables.
 * @env: Array of environment variables.
 * Return: None
 */
void printEnvironment(char **env)
{
	size_t index;

	for (index = 0; env[index]; index++)
	{
		write(STDOUT_FILENO, env[index], getStringLength(env[index]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
