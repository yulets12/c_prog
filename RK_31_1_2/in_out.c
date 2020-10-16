#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "in_out.h"
#include "errors.h"

int read_matrix(FILE *f, double **matrix, int *n, int *m)
{
    char str[MAX_LENGTH + 1];
    int len = 0;

    while (fgets(str, sizeof(str), f))
    {
        (*n)++;
        char *end_of_str = split(str);
        char *start = str, *end = NULL;
        double elem;

        while (start != end_of_str)
        {
            elem = strtod(start, &end);
            if (start == end && *end == '\0')
                start++;
            else
            {
                len++;
                *matrix = realloc(*matrix, len * sizeof(double));
                if (matrix)
                {
                    if (*end != '\0')
                        (*matrix)[len - 1] = NAN;
                    else
                        (*matrix)[len - 1] = elem;
                    start = end;
                    while (*start != '\0')
                        start++;
                    if (start < end_of_str)
                        start++;
                }
                else
                    return ERR_MEM;
            }
        }
    }
    if (*n > 0)
        (*m) = len / (*n);
    return OK;
}

char*split(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ' || str[i] == '\n')
            str[i] = '\0';
        i++;
    }
    return (str + i);
}

void print_matrix(double *matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (isnan(*(matrix + i * m + j)) == 0)
                printf("%-10.4lf ", *(matrix + i * m + j));
            else
                printf("%-10s", "NAN");

        }
        printf("\n");
    }
}
