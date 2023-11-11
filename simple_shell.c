#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

/**
 * main - Simple Shell
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		printf("#cisfun$ ");
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break; /* EOF (Ctrl+D) detected */
		}

		size_t len = strlen(input);
		if (len > 0 && input[len - 1] == '\n')
		{
			input[len - 1] = '\0'; /* remove newline */
		}

		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0) /* Child process */
		{
			execlp(input, input, (char *)NULL); /* Execute the command */
			perror(input); /* If execlp fails */
			exit(EXIT_FAILURE);
		}
		else /* Parent process */
		{
			int status;
			waitpid(child_pid, &status, 0);

			if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			{
				printf("%s: command not found\n", input);
			}
		}
	}

	return EXIT_SUCCESS;
}
