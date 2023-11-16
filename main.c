#include "shell.h"

/**
 * main - Main function for the shell.
 * @argc: Count of arguments.
 * @argv: Array of arguments.
 * @env: Environment variables.
 * Return: _exit value (0 by default).
 */
int main(int argc, char **argv, char **env)
{
	char *commandLine = NULL, **userCommand = NULL;
	int pathValue = 0, exitCode = 0, pathResult = 0;
	(void)argc;

	while (1)
	{
		commandLine = getCommandInput();
		if (commandLine)
		{
			pathValue++;
			userCommand = tokenizeString(commandLine);
			if (!userCommand)
			{
				free(commandLine);
				continue;
			}
			/*if ((!compareStrings(userCommand[0], "exit")) &&
					userCommand[1] == NULL)*/
			if (userCommand[0] != NULL && strcmp(userCommand[0],
						"exit") == 0 && userCommand[1] == NULL)
				exitShell(userCommand, commandLine, exitCode);
			if (!compareStrings(userCommand[0], "env"))
				printEnvironment(env);
			else
			{
				pathResult = findExecutablePath(&userCommand[0], env);
				exitCode = executeCommand(userCommand, argv,
						env, commandLine, pathValue, pathResult);
				if (pathResult == 0)
					free(userCommand[0]);
			}
			free(userCommand);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(exitCode);
		}
		free(commandLine);
	}
	return (exitCode);
}
