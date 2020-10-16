#include <stdlib.h>
#include <math.h>
#include "in_out.h"
#include "errors.h"

int main(int argc, char **argv)
{
    double *matrix = NULL;
    int n = 0, m = 0, rc = OK;
    FILE *f;

    if (argc != 2)
    {
        printf("app.exe file.txt");
        rc = ERR_ARGS;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (!f)
        {
            printf("Can't open the file.");
            rc = ERR_FILE;
        }
        else
        {
            rc = read_matrix(f, &matrix, &n, &m);
            if (rc != OK)
                printf("Memory error.");
            else
            {
                if (n == 0)
                    printf("File is empty.");
                else
                    print_matrix(matrix, n, m);
            }
        }
    }
    free(matrix);
    return rc;
}
