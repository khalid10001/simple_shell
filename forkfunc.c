#include "shell.h"

/**
 * executeCommand - Execute a command using fork and execve.
 * @command: Command and arguments.
 * @programName: Name of the shell program.
 * @environment: Array of environment variables.
 * @inputLine: Command line input from the user.
 * @processID: Process ID.
 * @checker: Checker for adding new tests.
 * Return: 0 on success.
 */
int executeCommand(char **command, char **programName, char **environment,
			char *inputLine, int processID, int checker)
{
	pid_t childPID;
	int status;
	char *notFoundFormat = "%s: %d: %s: not found\n";
	(void) checker;

	childPID = fork();

	if (childPID == 0)
	{
		if (execve(command[0], command, environment) == -1)
		{
			fprintf(stderr, notFoundFormat, programName[0], processID, command[0]);
		/*	if (!checker || checker)
				free(command[0]);*/
			free(command);
			free(inputLine);
			exit(errno);
		}
	}
	else
	{
		wait(&status);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
	}
	return (0);
}
