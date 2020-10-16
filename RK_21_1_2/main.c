#include <stdio.h>

#define OK 0
#define ERR_WRONG_CMD 1
#define ERR_IO 2
#define ERR_RANGE 3

int find(FILE *f, int *max)
{
    int num;

    if (fscanf(f, "%d", &num) == 1)
    {
        if (num % 2 == 1) *max = num;
        else
        {
            while ((fscanf(f, "%d", &num) == 1) && (num % 2 == 0))
            {
            }
            if (num % 2 == 1) *max = num;
            else return ERR_RANGE;
        }
        while (fscanf(f, "%d", &num) == 1)
        {
            if ((num % 2 == 1) && (num > *max)) *max = num;
        }
    }
    else return ERR_IO;
    return OK;
}

int main(int argc, char** argv)
{
    FILE *f;
    int rc = OK, result;


    if (argc == 2)
    {
        f = fopen(argv[1], "r");
        if (f)
        {
            rc = find(f, &result);
            if (rc == OK) printf("Result is %d", result);
            if (rc == ERR_IO) printf("There are no numbers in the file!");
            if (rc == ERR_RANGE) printf("There are no numbers which needed in the file!");
            fclose(f);
        }
        else
        {
            rc = ERR_IO;
            printf("Can't open the file!");
        }
    }
    else
    {
        rc = ERR_WRONG_CMD;
        printf("main.exe <file name>!");
    }
    return rc;
}
