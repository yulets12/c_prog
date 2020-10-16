#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct node node_t;
struct node
{
    char *fam;
    char *name;
    int year;
    int group;
    node_t *next;
};

#endif // STRUCTURE_H
