#include <string.h>
#include "errors.h"
#include "functions.h"
#include "in_out.h"

int main(int argc, char **argv)
{
    struct heads heads;
    FILE *fin, *fout;
    int rc = OK, choice, ch, height;
    //char *name, *surname, *club;
    char name[MAX_LENGTH + 1], surname[MAX_LENGTH + 1], club[MAX_LENGTH + 1];
    setbuf(stdout, NULL);
    if (argc != 3)
    {
        printf("<app.exe file_in.txt file_out.txt>\n");
        rc = ERR_ARGS;
    }
    else
    {
        fin = fopen(argv[1], "r");
        fout = fopen(argv[2], "w");
        if (!fin || !fout)
        {
            printf("Can't open the file!\n");
            rc = ERR_FILE;
        }
        else
        {
            heads_init(&heads);
            while (1)
            {
                print_menu();
                choice = get_choice(0, 10);
                switch (choice)
                {
                    case 1:
                        rc = read_file(fin, &heads);
                        break;
                    case 2:
                        rc = add_rec(&heads);
                        break;
                    case 3:
                        printf("Input the surname to delete: ");
                        fscanf(fin, "%s", surname);
                        printf("Input the name to delete: ");
                        fscanf(fin, "%s", name);
                        del_rec(&heads, name, surname);
                        break;
                    case 4:
                        printf("Input min height: ");
                        while (scanf("%d", &height)!= 1)
                        {
                            printf("\nInput error! Input int: ");
                            fflush(stdin);
                        }
                        fflush(stdin);
                        player_t player;
                        player.height = height;
                        heads.filter[0] = filter(heads.filter[0], heads.foffsetof[0], &player, fcmpr_height);
                        break;
                    case 5:
                        printf("Input club: ");
                        while (scanf("%s", club)!= 1)
                        {
                            printf("\nInput error! Input str: ");
                            fflush(stdin);
                        }
                        fflush(stdin);
                        player_t pl;
                        strcpy(pl.club, club);
                        heads.filter[1] = filter(heads.filter[1], heads.foffsetof[1], &pl, fcmpr_club);
                        break;
                    case 6:
                        heads.sort[0] = sort(heads.sort[0], heads.soffsetof[0], scmpr_surname);
                        break;
                    case 7:
                        heads.sort[1] = sort(heads.sort[1], heads.soffsetof[1], scmpr_year);
                        break;
                    case 8:
                        heads.sort[2] = sort(heads.sort[2], heads.soffsetof[2], scmpr_height);
                        break;
                    case 9:
                        print_ch();
                        ch = get_choice(1, 5);
                        switch (ch)
                        {
                            case 1:
                                print_dir(heads.sort[0], heads.soffsetof[0]);
                                break;
                            case 2:
                                print_dir(heads.sort[1], heads.soffsetof[1]);
                                break;
                            case 3:
                                print_dir(heads.sort[2], heads.soffsetof[2]);
                                break;
                            case 4:
                                print_dir(heads.filter[0], heads.foffsetof[0]);
                                break;
                            case 5:
                                print_dir(heads.filter[1], heads.foffsetof[1]);
                                break;
                        }
                        break;
                    case 10:
                        print_ch();
                        ch = get_choice(1, 5);
                        switch (ch)
                        {
                            case 1:
                                save_to_file(fout, heads.sort[0], heads.soffsetof[0]);
                                break;
                            case 2:
                                save_to_file(fout, heads.sort[1], heads.soffsetof[1]);
                                break;
                            case 3:
                                save_to_file(fout, heads.sort[2], heads.soffsetof[2]);
                                break;
                            case 4:
                                save_to_file(fout, heads.filter[0], heads.foffsetof[0]);
                                break;
                            case 5:
                                save_to_file(fout, heads.filter[1], heads.foffsetof[1]);
                                break;
                        }
                    case 0:
                        break;
                }
                if (rc != OK)
                    break;
            }
            free_all(&heads);
            fclose(fin);
            fclose(fout);
        }
    }
    return rc;
}
