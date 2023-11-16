#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    char *command;

    while (1)
    {
        display_prompt();
        command = read_line();

        if (command == NULL)
        {
            printf("\n");
            break; /* End of file condition (Ctrl+D) */
        }

        if (strlen(command) > 0)
            execute_command(command);

        free(command);
    }

    return 0;
}
