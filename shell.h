#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/* 0. printenv with environ */
void print_env(void);

/* 1. env vs environ */
void env_vs_environ(void);

/* 2. getenv() */
char *_getenv(const char *name);

/* 3. PATH */
void print_path_directories(void);

/* 4. PATH */
typedef struct PathNode {
    char *directory;
    struct PathNode *next;
} PathNode;

PathNode *build_path_linked_list(void);

/* 5. setenv */
int _setenv(const char *name, const char *value, int overwrite);

/* 6. unsetenv */
int _unsetenv(const char *name);

/* 10. cd */
void cd_builtin(char *directory);

#endif /* SHELL_H */
