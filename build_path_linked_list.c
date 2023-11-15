#include "shell.h"

/**
 * main - Entry point for the build_path_linked_list program.
 * Return: Always 0.
 */
/*int main(void)
{
    printf("Linked list of PATH directories:\n");
    build_path_linked_list();
    return 0;
}
*/
void *add_node_end(path_list_t **head, char *directory);
void print_path_list(path_list_t *head);
void free_path_list(path_list_t *head);

/**
 * add_node_end - Add a new node at the end of the linked list
 * @head: A pointer to the head of the linked list
 * @directory: The directory to be added to the linked list
 * Return: A pointer to the newly added node
 */
void *add_node_end(path_list_t **head, char *directory)
{
    path_list_t *new_node = malloc(sizeof(path_list_t));
    path_list_t *last = *head;

    if (new_node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    new_node->directory = strdup(directory);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }

    return new_node;
}


/**
 * build_path_linked_list - Builds a linked list of directories in the PATH.
 */
void build_path_linked_lists(void)
{
    char *path_variable = "PATH";
    char *path_value = _getenv(path_variable);

    path_list_t *head = NULL;
    add_node_end(&head, "some_directory");
    print_path_list(head);
    free_path_list(head);

    if (path_value != NULL)
    {
        path_list_t *head = NULL;
        char *directory = strtok(path_value, ":");

        while (directory != NULL)
        {
            add_node_end(&head, directory);
            directory = strtok(NULL, ":");
        }

        print_path_list(head);
        free_path_list(head);
    }
    else
    {
        printf("PATH variable not found.\n");
    }
}

/**
 * print_path_list - Prints each node in the linked list.
 * @head: Pointer to the head of the linked list.
 */
void print_path_list(path_list_t *head)
{
    while (head != NULL)
    {
        printf("%s\n", head->directory);
        head = head->next;
    }
}

/**
 * free_path_list - Frees the memory allocated for the linked list.
 * @head: Pointer to the head of the linked list.
 */
void free_path_list(path_list_t *head)
{
    while (head != NULL)
    {
        path_list_t *temp = head;
        head = head->next;
        free(temp->directory);
        free(temp);
    }
}
