#include <stdio.h>

#define OK 0
#define ERR_WRONG_CMD 1
#define ERR_FILE 2
#define ERR_RANGE 3
#define N 100

int input(FILE *f, int *pbeg, int **pend);
void print(const int *pbeg, const int *pend);
int check(const int *pcur, const int *pbeg);
int solve(const int *pbeg, const int *pend);

int main(int argc, char **argv)
{
    FILE *f;
    int rc = OK, a[N], result;
    int  *pbeg = a, *pend = a;

    if (argc != 2)
    {
        printf("main.exe file_name!!!\n");
        rc = ERR_WRONG_CMD;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (f)
        {
            rc = input(f, pbeg, &pend);
            if ((rc == ERR_RANGE) || (rc == OK))
            {
                if (rc == ERR_RANGE)
                    printf("There are more than %d numbers in the file.\n", N);
                if (pbeg == pend)
                    printf("There are no numbers in the file");
                else
                {
                    print(pbeg, pend);
                    result = solve(pbeg, pend);
                    printf("Amount of different numbers in the file is %d", result);
                }
            }
            else
                printf("Input error %d", rc);
            fclose(f);
        }
        else
        {
            printf("Can't open the file!!!");
            rc = ERR_FILE;
        }
    }
    return rc;
}
