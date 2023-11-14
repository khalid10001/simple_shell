#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Function declarations
void env_shell(void);
void exit_shell(void);
int execute_command(char *command);

#endif /* MAIN_H */
