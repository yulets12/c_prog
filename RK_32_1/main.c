#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "in_out.h"

int main(int argc, char **argv)
{
    node_t *head;
    FILE *f;
    int rc = OK;
    if (argc != 3 && argc != 4)
    {
        print_inf();
        rc = ERR_ARGS;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (!f)
        {
            printf("Can't open the file.\n");
            print_inf();
            rc = ERR_FILE;
        }
        else
        {
            head = read_file(f, &rc);
            if (rc == OK)
            {
                if (!strcmp(argv[2], "list"))
                    print_list(head);
                else
                {
                    if (!strcmp(argv[2], "rd"))
                    {
                        remove_duplicates(&head, cmpr_elems);
                        print_list(head);
                    }
                    else
                    {
                        if (!strcmp(argv[2], "select") && argc == 4)
                        {
                            select(head, argv[3]);
                        }
                        else
                        {
                            print_inf();
                            rc = ERR_ARGS;
                        }
                    }
                }
                free_list(head);
            }
            fclose(f);
        }
    }
    if (rc == ERR_EMPTY)
        printf("File is empty.\n");
    if (rc == ERR_IO)
        printf("Input error.");
    return rc;
}
