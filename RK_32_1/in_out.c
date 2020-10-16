#include <stdlib.h>
#include <string.h>
#include "in_out.h"

node_t*create_node(char *fam, char *name, int year, int group)
{  
    char *new_fam = strdup(fam);
    if (!new_fam)
        return NULL;
    char *new_name = strdup(name);
    if (!new_name)
    {
        free(new_fam);
        return NULL;
    }
    node_t *new_node = NULL;
    new_node = malloc(sizeof(node_t));
    if (!new_node)
    {
        free(new_fam);
        free(new_name);
        return NULL;
    }
    new_node->fam = new_fam;
    new_node->name = new_name;
    new_node->year = year;
    new_node->group = group;
    new_node->next = NULL;
    return new_node;
}

node_t*add_node(node_t *head, node_t *elem)
{
    if (!head)
        return elem;
    node_t *cur = head;
    for (; cur->next; cur = cur->next);
    cur->next = elem;
    return head;
}

void free_list(node_t *head)
{
    node_t *tmp;
    for (;head; head = tmp)
    {
        free(head->fam);
        free(head->name);
        tmp = head->next;
        free(head);
    }
}
node_t*read_file(FILE *f, int *rc)
{
    char name[MAX_LEN + 1], fam[MAX_LEN + 1], smb;
    int year, group;
    node_t *head = NULL, *new;
    while (!feof(f))
    {
        if (!fgets(fam, MAX_LEN, f))
        {
            if (!head)
                *rc = ERR_EMPTY;
            else
                *rc = ERR_IO;
            free_list(head);
            return NULL;
        }
        if (fam[strlen(fam) - 1] == '\n')
            fam[strlen(fam) - 1] = '\0';        
        if (!fgets(name, MAX_LEN, f))
        {
            *rc = ERR_IO;
            free_list(head);
            return NULL;
        }
        if (name[strlen(name) - 1] == '\n')
            name[strlen(name) - 1] = '\0';
        if (fscanf(f, "%d", &year) != 1)
        {
            *rc = ERR_IO;
            free_list(head);
            return NULL;
        }
        fscanf(f, "%c", &smb);
        if (fscanf(f, "%d", &group) != 1)
        {
            *rc = ERR_IO;
            free_list(head);
            return NULL;
        }
        fscanf(f, "%c", &smb);
        new = create_node(fam, name, year, group);
        if (!new)
        {
            *rc = ERR_MEM;
            free_list(head);
            return NULL;
        }
        head = add_node(head, new);
    }
    return head;
}

void print_inf(void)
{
    printf("<app.exe file.txt action [str]>\n");
    printf("actions:\n\t-list\n\t-select str\n\t-rd");
}

void print_list(node_t *head)
{
    printf("%-30s|%-30s|%-5s|%-5s\n", "surname", "name", "year", "group");
    for (int i = 0; i < 75; i++)
        printf("-");
    printf("\n");
    for (; head; head = head->next)
        printf("%-30s|%-30s|%-5d|%-5d\n", head->fam, head->name, head->year, head->group);
}
