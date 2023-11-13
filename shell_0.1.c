#include "main.h"

/**
 * main - Simple Shell 0.1
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
			input[len - 1] = '\0'; /* remove newline */

		execute_command(input);
	}

	return EXIT_SUCCESS;
}
