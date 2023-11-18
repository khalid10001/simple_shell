#ifndef SHELL_H
#define SHELL_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

int compareStrings(char *s1, char *s2);
size_t compareStringsN(char *s1, char *s2, size_t n);
int getStringLength(char *s);
char *copyString(char *dest, char *src);
char *concatenateStrings(char *dest, char *src);
int customPutchar(char c);

char *getPath(char **env);
int findExecutablePath(char **command, char **environment);
char *getCommandInput(void);
void printEnvironment(char **env);
char **tokenizeString(char *userInput);
void exitShell(char **args, char *inputLine, int exitValue);
int executeCommand(char **command, char **programName, char **environment,
			char *inputLine, int processID, int checker);
char *customStrtok(char *str, const char *delimiters);
int setenvCommand(char **args, char **env);
int unsetenvCommand(char **args, char **env);
int startsWith(const char *str, const char *prefix);
int setEnvVariable(char *variable, char *value, char **env);
int unsetEnvVariable(char *variable, char **env);
#endif /* SHELL_H */

