#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structure.h"

void remove_duplicates(node_t **head, int (*comparator)(node_t*, node_t*));
int cmpr_elems(node_t *elem1, node_t *elem2);
int is_substring(const char *str, const char *substr);
void select(node_t *head, const char *substr);

#endif // FUNCTIONS_H
