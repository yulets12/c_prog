#ifndef IN_OUT_H
#define IN_OUT_H
#include <stdio.h>
#include "structure.h"
#define MAX_LEN 70
#define OK 0
#define ERR_MEM 1
#define ERR_FILE 2
#define ERR_IO 3
#define ERR_ARGS 4
#define ERR_EMPTY 5

node_t*create_node(char *fam, char *name, int year, int group);
node_t*add_node(node_t *head, node_t *elem);
void free_list(node_t *head);
node_t*read_file(FILE *f, int *rc);
void print_inf(void);
void print_list(node_t *head);

#endif // IN_OUT_H
