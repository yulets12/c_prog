#include <string.h>
#include <stdlib.h>
#include "functions.h"

int fcmpr_club(player_t *pl, void *data)
{
    char *club = data;
    return strcmp(pl->club, club);
}

int fcmpr_height(player_t *pl, void *data)
{
    int *height = data;
    if (pl->height >= *height)
        return 0;
    return 1;
}

void remove_elem(struct list_head *elem)
{
    struct list_head *next = elem->next, *prev = elem->prev;
    prev->next = next;
    next->prev = prev;
    elem->next = NULL;
    elem->prev = NULL;
}
struct list_head*filter(struct list_head *head, unsigned int offsetof, void *data, int comparator(player_t*, void*))
{
    if (!head)
        return NULL;
    struct list_head *cur = head;
    do
    {
        struct list_head *next = cur->next;
        if (!comparator((player_t *)((char*)(cur) - offsetof), data))
        {
            remove_elem(cur);
            if (cur == head)
            {
                if (next == cur)
                    head = NULL;
                else
                    head = next;
            }
        }
        cur = next;
    }
    while (cur != head && head != NULL);
    return head;
}

int scmpr_height(player_t *pl1, player_t *pl2)
{
    int res;
    if ((res = pl1->height - pl2->height) != 0)
        return res;
    if ((res = strcmp(pl1->surname, pl2->surname)) != 0)
        return res;
    if ((res = strcmp(pl1->name, pl2->name)) != 0)
        return res;
    if ((res = strcmp(pl1->club, pl2->club)) != 0)
        return res;
    if ((res = pl1->year - pl2->year) != 0)
        return res;
    return 0;
}

int scmpr_year(player_t *pl1, player_t *pl2)
{
    int res;
    if ((res = pl1->year - pl2->year) != 0)
        return res;
    if ((res = strcmp(pl1->surname, pl2->surname)) != 0)
        return res;
    if ((res = strcmp(pl1->name, pl2->name)) != 0)
        return res;
    if ((res = strcmp(pl1->club, pl2->club)) != 0)
        return res;
    if ((res = pl1->height - pl2->height) != 0)
        return res;
    return 0;
}

int scmpr_surname(player_t *pl1, player_t *pl2)
{
    int res;
    if ((res = strcmp(pl1->surname, pl2->surname)) != 0)
        return res;
    if ((res = strcmp(pl1->name, pl2->name)) != 0)
        return res;
    if ((res = strcmp(pl1->club, pl2->club)) != 0)
        return res;
    if ((res = pl1->height - pl2->height) != 0)
        return res;
    if ((res = pl1->year - pl2->year) != 0)
        return res;
    return 0;
}

void insert(struct list_head *elem, struct list_head **before)
{
    if (!(*before))
    {
        elem->next = elem;
        elem->prev = elem;
        *before = elem;
    }
    else
    {
        struct list_head *prev = (*before)->prev;
        prev->next = elem;
        elem->prev = prev;
        (*before)->prev = elem;
        elem->next = *before;
    }
}

struct list_head*sort(struct list_head *head, unsigned int offsetof, int comparator(player_t*, player_t*))
{
    if (!head)
        return NULL;
    struct list_head *cur = head;
    do
    {
        struct list_head *cur_sorted = head, *next = cur->next;
        for (; cur_sorted != cur; cur_sorted = cur_sorted->next)
            if (comparator((player_t *)((char*)(cur) - offsetof), (player_t *)((char*)(cur_sorted) - offsetof)) < 0)
                break;
        if (cur != cur_sorted)
        {
            remove_elem(cur);
            insert(cur, &cur_sorted);
            if (cur_sorted == head)
                head = cur;
        }
        cur = next;
    }
    while (cur != head);
    return head;
}

int dcmpr(player_t *pl, char *name, char *surname)
{
    if (!strcmp(pl->name, name) && !strcmp(pl->surname, surname))
        return 0;
    return 1;
}

void remove_elem_from_lists(struct heads *heads, player_t *player)
{
    for (int i = 0; i < MAX_SORT_INDX; i++)
    {
        remove_elem(&(player->sort[i]));
        if (&(player->sort[i]) == heads->sort[i])
        {
            if (heads->sort[i]->next == heads->sort[i])
                heads->sort[i] = NULL;
            else
                heads->sort[i] = heads->sort[i]->next;
        }
    }
    for (int i = 0; i < MAX_FILTER_INDX; i++)
    {
        remove_elem(&(player->filter[i]));
        if (&(player->filter[i]) == heads->filter[i])
        {
            if (heads->filter[i]->next == heads->filter[i])
                heads->filter[i] = NULL;
            else
                heads->filter[i] = heads->filter[i]->next;
        }
    }
    free(player);
}

void del_rec(struct heads *heads, char *name, char *surname)
{
    if (!heads->sort[0])
        return;
    struct list_head *cur = heads->sort[0];
    do
    {
        struct list_head *next = cur->next;
        player_t *player = (player_t *)((char*)(cur) - heads->soffsetof[0]);
        if (!dcmpr(player, name, surname))
            remove_elem_from_lists(heads, player);
        cur = next;
    }
    while (cur != heads->sort[0] && heads->sort[0] != NULL);
}
