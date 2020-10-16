#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "in_out.h"

int cmpr_elems(node_t *elem1, node_t *elem2)
{
    if (!strcmp(elem1->fam, elem2->fam) && !strcmp(elem1->name, elem2->name) && !(elem1->group - elem2->group) && !(elem1->year - elem2->year))
            return 0;
        else
            return 1;
}

void remove_duplicates(node_t **head, int (*comparator)(node_t*, node_t*))
{
    node_t *prev;
    for (node_t *cur = *head; cur && cur->next; cur = cur->next)
    {
        prev = cur;
        for (node_t *next = cur->next; next; next = next->next)
        {
            if (!comparator(cur, next))
            {
                prev->next = next->next;
                free(next->fam);
                free(next->name);
                free(next);
                next = prev;
            }
            else
                prev = next;
        }
    }
}


int is_substring(const char *str, const char *substr)
{
int i = 0;
while (str[i] != '\0' && substr[i] != '\0')
{
    if (str[i] != substr[i])
        return 0;
    i++;
}
if (str[i] == '\0' && substr[i] != '\0')
    return 0;
return 1;
}

void select(node_t *head, const char *substr)
{
    printf("%-30s|%-30s|%-5s|%-5s\n", "second name", "first name", "year", "group");
    for (int i = 0; i < 75; i++)
        printf("-");
    printf("\n");
    for (; head; head = head->next)
    {
        if (is_substring(head->fam, substr))
            printf("%-30s|%-30s|%-5d|%-5d\n", head->fam, head->name, head->year, head->group);
    }
}
