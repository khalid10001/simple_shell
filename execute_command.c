#include "main.h"

/**
 * execute_command - Execute a command in a child process.
 * @input: The command to execute.
 * Return: 0 on success, 1 on failure.
 */
int execute_command(char *input)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0) /* Child process */
	{
		execlp(input, input, (char *)NULL); /* Execute the command */
		perror("execlp"); /* If execlp fails */
		exit(EXIT_FAILURE);
	}
	else /* Parent process */
	{
		int status;
		waitpid(child_pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		{
			fprintf(stderr, "%s: command not found\n", input);
		}
	}

	return 0;
}
