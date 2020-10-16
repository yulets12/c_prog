#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structure.h"

struct list_head*filter(struct list_head *head, unsigned int offsetof, void *data, int comparator(player_t*, void*));
void remove_elem(struct list_head *elem);
int fcmpr_club(player_t *pl, void *data);
int fcmpr_height(player_t *pl, void *data);
int scmpr_height(player_t *pl1, player_t *pl2);
int scmpr_year(player_t *pl1, player_t *pl2);
int scmpr_surname(player_t *pl1, player_t *pl2);
void insert(struct list_head *elem, struct list_head **before);
struct list_head*sort(struct list_head *head, unsigned int offsetof, int comparator(player_t*, player_t*));
void del_rec(struct heads *heads, char *name, char *surname);
void remove_elem_from_lists(struct heads *heads, player_t *player);

#endif // FUNCTIONS_H
