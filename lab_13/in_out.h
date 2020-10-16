#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>
#include "structure.h"

void print_ch(void);
int get_choice(int from, int to);
void print_menu(void);
void print_dir(struct list_head *head, unsigned int offsetoff);
void save_to_file(FILE *f, struct list_head *head, unsigned int offsetoff);
player_t*create_player(char *surname, char *name, char *club, int height, int year);
int add_rec(struct heads *heads);
void heads_init(struct heads *heads);
void free_all(struct heads *heads);
int read_file(FILE *f, struct heads *heads);

#endif // IN_OUT_H
