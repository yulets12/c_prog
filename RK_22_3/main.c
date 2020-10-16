#include <stdio.h>
#include "in_out.h"
#include "process.h"
#include "err.h"

int main(int argc,char **argv)
{
    FILE *fx, *fy;
    int x[N], y[N], n, m, rcx, rcy, k, result = 0, rc = OK;
    setbuf(stdout, NULL);
    if (argc != 3)
    {
        printf("main.exe  file_for_x  file_for_y !");
        rc = ERR_CMD;
    }
    else
    {
        fx = fopen(argv[1],"r");
        fy = fopen(argv[2],"r");
        if (!fx && !fy)
        {
            printf("Can't open the files!");
            rc = ERR_FILE;
        }
        else
        {
            rcx = input(fx, x, &n);
            rcy = input(fy, y, &m);
            if (rcx == ERR_IO ||  rcy == ERR_IO)
            {
                printf("Files must include only int meanings!");
                rc = ERR_IO;
            }
            else
                if (rcx == ERR_RANGE || rcy == ERR_RANGE)
                {
                    printf("Wrong length of array!");
                    rc = ERR_RANGE;
                }
                else
                {
                    fclose(fx);
                    fclose(fy);
                    printf("Array x:\n");
                    output(x, n);
                    printf("Array y:\n");
                    output(y, m);
                    printf("Input k: ");
                    if (scanf("%d", &k) != 1)
                    {
                        printf("k must be int!");
                        rc = ERR_IO;
                    }
                    else
                    {
                        if (k < 0 || k > m)
                        {
                            printf("Wrong k!");
                            rc = ERR_RANGE;
                        }
                        else
                        {
                            if (solve(x, n, y, m, k, &result) == ERR_RANGE)
                            {
                                printf("n > m !");
                                rc = ERR_RANGE;
                            }
                            else
                                printf("Result is %d", result);
                        }
                    }
                }
        }
    }
    return rc;
}
