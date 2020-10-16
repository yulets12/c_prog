#include "functions.h"
#include "errors.h"

int main(int argc, char **argv)
{
    FILE *f_in, *f_out;
    int rc = OK;
    if (argc != 7)
    {
        printf("app.exe in.txt out.txt -s search -r replace");
        rc = ERR_ARGS;
    }
    else
    {
        f_in = fopen(argv[1], "r");
        if (f_in)
        {
            f_out = fopen(argv[2], "w");
            if (f_out)
            {
                if (str_cmpr(argv[3], "-s") && str_cmpr(argv[5], "-r"))
                {
                    rc = process(f_in, f_out, argv[4], argv[6]);
                    fclose(f_out);
                }
                else
                {
                    printf("app.exe in.txt out.txt -s search -r replace");
                    rc = ERR_ARGS;
                }
            }
            else
            {
                rc = ERR_FILE;
                printf("Error code: %d\n", rc);
            }
            fclose(f_in);
        }
        else
        {
            rc = ERR_FILE;
            printf("Error code: %d\n", rc);
        }
    }
    printf("%d", rc);
    return rc;
}
