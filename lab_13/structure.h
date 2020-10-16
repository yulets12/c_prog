#ifndef STRUCTURE_H
#define STRUCTURE_H
#define MAX_LENGTH 50
#define MAX_SORT_INDX 3
#define MAX_FILTER_INDX 2

struct list_head
{
    struct list_head *next, *prev;
};

typedef struct player player_t;
struct player
{
    char surname[MAX_LENGTH + 1];
    char name[MAX_LENGTH + 1];
    char club[MAX_LENGTH + 1];
    int height, year;
    struct list_head sort[MAX_SORT_INDX];
    struct list_head filter[MAX_FILTER_INDX];
};

struct heads
{
    struct list_head *sort[MAX_SORT_INDX];
    struct list_head *filter[MAX_FILTER_INDX];
    unsigned int soffsetof[MAX_SORT_INDX];
    unsigned int foffsetof[MAX_FILTER_INDX];
};

#endif // STRUCTURE_H
