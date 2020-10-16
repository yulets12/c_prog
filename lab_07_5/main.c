#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "in_out.h"
#include "filter.h"
#include "sort.h"

int main(int argc, char **argv)
{
    int rc = OK;
    FILE *f_in, *f_out;

    if (argc == 3 || argc == 4)
    {
        f_in = fopen(argv[1], "r");
        if (f_in)
        {
            f_out = fopen(argv[2], "w");
            if (f_out)
            {
                int *pabeg = NULL, *paend = NULL;
                rc = read(f_in, &pabeg, &paend);
                if (rc == OK)
                {
                    print(pabeg, paend);
                    if (argc == 4 && strcmp(argv[3], "f") == 0)
                    {
                        int *pbbeg = NULL, *pbend = NULL;
                        rc = key(pabeg, paend, &pbbeg, &pbend);

                        if (rc == OK)
                            solve(f_out, pbbeg, pbend);
                        else
                        {
                            if (rc == ERR_MEM)
                                printf("Memory error!");
                            if (rc == ERR_EMPTY)
                                printf("Result array is empty after the filtering!");
                            if (rc == ERR_PARAM)
                                printf("Filter-function has got wrong parameters!");
                        }
                        free(pbbeg);
                    }
                    else
                    {
                        if (argc == 4)
                            rc = ERR_ARGS;
                        else
                            solve(f_out, pabeg, paend);
                    }
                    free(pabeg);
                }
                else
                {
                    if (rc == ERR_MEM)
                        printf("Memory error!");
                    if (rc == ERR_EMPTY)
                        printf("There are no numbers in the file!");
                }
                fclose(f_out);
            }
            else
            {
                rc = ERR_IO;
                printf("Can't open out_file!");
            }
            fclose(f_in);
        }
        else
        {
            rc = ERR_IO;
            printf("Can't open in_file!");
        }
    }
    else
    {
        rc = ERR_ARGS;
        printf("app.exe in_file out_file [f]");
    }
    return rc;
}
