#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * exit_shell - Exit the shell
 */
void exit_shell(void)
{
    printf("Exiting the shell\n");
    exit(EXIT_SUCCESS);
}
