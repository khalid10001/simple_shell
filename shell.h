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
extern char **environ;
int _setenviron(const char *name, const char *value, int overwrite);
int _unsetenviron(const char *name);
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

/* Definition of a structure to represent a node in the linked list */
typedef struct path_list {
    char *directory;
    struct path_list *next;
} path_list_t;

/* Function prototypes */
path_list_t *add_node_end(path_list_t **head, char *directory);
void print_path_list(path_list_t *head);
void free_path_list(path_list_t *head);

/* 5. setenv */
int _setenv(const char *name, const char *value, int overwrite);

/* 6. unsetenv */
int _unsetenv(const char *name);

/* 10. cd */
void cd_builtin(char *directory);

#endif /* SHELL_H */
