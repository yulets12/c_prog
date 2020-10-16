#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "in_out.h"
#include "errors.h"
#include "functions.h"

int get_choice(int from, int to)
{
    int choice;
    while (scanf("%d", &choice)!= 1 || choice < from || choice > to)
    {
        printf("\nInput error! Choose again (int 0 - 10): ");
        fflush(stdin);
    }
    fflush(stdin);
    return choice;
}

void print_ch(void)
{
    printf("Choose information to print:\n");
    printf("1. Sorted by surname.\n");
    printf("2. Sorted by year.\n");
    printf("3. Sorted by height.\n");
    printf("4. Filtered by height.\n");
    printf("5. Filtered by club.\n\n");
}

void print_menu(void)
{
    printf("Choose the action:\n");
    printf("1. Load data from file.\n");
    printf("2. Add record.\n");
    printf("3. Delete record by name and surname.\n");
    printf("4. Filter by height.\n");
    printf("5. Filter by club.\n");
    printf("6. Sort by surname.\n");
    printf("7. Sort by year.\n");
    printf("8. Sort by height.\n");
    printf("9. Print on screen.\n");
    printf("10. Save to the file.\n\n");
    printf("0. Exit.\n\n");
}

int read_file(FILE *f, struct heads *heads)
{
    player_t *player;
    char name[MAX_LENGTH + 1], surname[MAX_LENGTH + 1], club[MAX_LENGTH + 1], smb;
    int height, year, cnt, k;
    while (!feof(f))
    {
        height = 0, year = 0;
        k = 0;
        cnt = 0;
        while (fscanf(f, "%c", &smb) == 1 && smb != ';')
        {
            if (smb != ' ')
            {
                if (cnt < MAX_LENGTH)
                {
                    surname[cnt] = smb;
                    cnt++;
                }
                else
                    return ERR_IO;
            }
        }
        if (smb == ';')
            k++;
        if (cnt == 0)
            return ERR_IO;
        surname[cnt] = '\0';

        cnt = 0;
        while (fscanf(f, "%c", &smb) == 1 && smb != ';')
        {
            if (smb != ' ')
            {
                if (cnt < MAX_LENGTH)
                {
                    name[cnt] = smb;
                    cnt++;
                }
                else
                    return ERR_IO;
            }
        }
        if (smb == ';')
            k++;
        if (cnt == 0)
            return ERR_IO;
        name[cnt] = '\0';

        cnt = 0;
        while (fscanf(f, "%c", &smb) == 1 && smb != ';')
        {
            if (smb != ' ')
            {
                if (cnt < MAX_LENGTH)
                {
                    club[cnt] = smb;
                    cnt++;
                }
                else
                    return ERR_IO;
            }
        }
        if (smb == ';')
            k++;
        if (cnt == 0)
            return ERR_IO;
        club[cnt] = '\0';

        cnt = 0;
        while (fscanf(f, "%c", &smb) == 1 && smb != ';')
        {
            if (smb != ' ')
            {
                if (cnt < 3)
                {
                    if (smb >= '0' && smb <= '9')
                    {
                        height += (smb - '0') * pow(10, 2 - cnt);
                        cnt++;
                    }
                    else
                        return ERR_IO;
                }
                else
                    return ERR_IO;
            }
        }
        if (smb == ';')
            k++;
        if (cnt == 0)
            return ERR_IO;

        if (k != 4)
            return ERR_IO;

        cnt = 0;
        while (fscanf(f, "%c", &smb) == 1 && smb != '\n')
        {
            if (smb != ' ')
            {
                if (cnt < 4)
                {
                    if (smb >= '0' && smb <= '9')
                    {
                        year += (smb - '0') * pow(10, 3 - cnt);
                        cnt++;
                    }
                    else
                        return ERR_IO;
                }
                else
                    return ERR_IO;
            }
        }
        if (cnt == 0)
            return ERR_IO;
    player = create_player(surname, name, club, height, year);
    if (!player)
        return ERR_MEM;
    for (int i = 0; i < MAX_SORT_INDX; i++)
        insert(&(player->sort[i]), &(heads->sort[i]));
    for (int i = 0; i < MAX_FILTER_INDX; i++)
        insert(&(player->filter[i]), &(heads->filter[i]));
//    printf("%p\n", (void *)player);
    }
    return OK;
}

void print_dir(struct list_head *head, unsigned int offsetoff)
{
    if (!head)
        printf("List is empty!\n");
    else
    {
        printf("%-30s|%-30s|%-30s|%-10s|%-10s\n", "Surname", "Name", "Club", "Height", "Year");
        for (int i = 0; i < 120; i++)
            printf("-");
        printf("\n");
        struct list_head *cur = head;
        do
        {
            player_t *data = (player_t *)((char*)(cur) - offsetoff);
//            printf("%p\n", (void*)data);
            printf("%-30s|%-30s|%-30s|%-10d|%-10d\n", data->surname, data->name, data->club, data->height, data->year);
            cur = cur->next;
        }
        while (cur != head);
    }
}

void save_to_file(FILE *f, struct list_head *head, unsigned int offsetoff)
{
    if (head)
    {
        struct list_head *cur = head;
        do
        {
            player_t *data = (player_t *)((char*)(cur) - offsetoff);
            fprintf(f, "%s;%s;%s;%d;%d\n", data->surname, data->name, data->club, data->height, data->year);
            cur = cur->next;
        }
        while (cur != head);
    }
}

player_t*create_player(char *surname, char *name, char *club, int height, int year)
{
    player_t *new_player = malloc(sizeof(player_t));
    if (new_player)
    {
        strcpy(new_player->surname, surname);
        strcpy(new_player->name, name);
        strcpy(new_player->club, club);
        new_player->height = height;
        new_player->year = year;
        for (int i = 0; i < MAX_SORT_INDX; i++)
        {
            new_player->sort[i].next = NULL;
            new_player->sort[i].prev = NULL;
        }
        for (int i = 0; i < MAX_FILTER_INDX; i++)
        {
            new_player->filter[i].next = NULL;
            new_player->filter[i].prev = NULL;
        }
    }
    return new_player;
}

int add_rec(struct heads *heads)
{
    char surname[MAX_LENGTH + 1];
    char name[MAX_LENGTH + 1];
    char club[MAX_LENGTH + 1];
    int year, height;
    printf("Input surname: ");
    while (scanf("%s", surname) != 1)
    {
        printf("Input error! Try again: ");
        fflush(stdin);
    }
    fflush(stdin);
    printf("Input name: ");
    while (scanf("%s", name) != 1)
    {
        printf("Input error! Try again: ");
        fflush(stdin);
    }
    fflush(stdin);
    printf("Input club: ");
    while (scanf("%s", club) != 1)
    {
        printf("Input error! Try again: ");
        fflush(stdin);
    }
    fflush(stdin);
    printf("Input height: ");
    while (scanf("%d", &height) != 1)
    {
        printf("Input error! Try again: ");
        fflush(stdin);
    }
    fflush(stdin);
    printf("Input year: ");
    while (scanf("%d", &year) != 1)
    {
        printf("Input error! Try again: ");
        fflush(stdin);
    }
    fflush(stdin);
    player_t *new = create_player(surname, name, club, height, year);
    if (!new)
        return ERR_MEM;
    for (int i = 0; i < MAX_SORT_INDX; i++)
        insert(&(new->sort[i]), &(heads->sort[i]));
    for (int i = 0; i < MAX_FILTER_INDX; i++)
        insert(&(new->filter[i]), &(heads->filter[i]));
    return OK;
}

void heads_init(struct heads *heads)
{
    for (int i = 0; i < MAX_SORT_INDX; i++)
        heads->sort[i] = NULL;
    for (int i = 0; i < MAX_FILTER_INDX; i++)
        heads->filter[i] = NULL;
    for (int i = 0; i < MAX_SORT_INDX; i++)
        heads->soffsetof[i] = (uintptr_t)(&(((player_t *) 0)->sort[i]));
//    printf("%d\n", (int) heads->soffsetof[0]);
//    printf("%d\n", (int) heads->soffsetof[2]);
    for (int i = 0; i < MAX_FILTER_INDX; i++)
        heads->foffsetof[i] = (uintptr_t)(&(((player_t *) 0)->filter[i]));
}

void free_all(struct heads *heads)
{
    if (heads->sort[0])
    {
        struct list_head *cur = heads->sort[0];
        do
        {
            struct list_head *next = cur->next;
            if (cur == next)
                next = NULL;
            player_t *player = (player_t*)((char*)(cur) - heads->soffsetof[0]);
            remove_elem(cur);
            free(player);
            cur = next;
        }
        while (cur != NULL);
    }
    for (int i = 0; i < MAX_SORT_INDX; i++)
        heads->sort[i] = NULL;
    for (int i = 0; i < MAX_FILTER_INDX; i++)
        heads->filter[i] = NULL;
}
