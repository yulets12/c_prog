#include <stdio.h>
#include <string.h>
#include "in_out.h"
#include "operations.h"
#include "errors.h"

int main(int argc, char **argv)
{
    double **matrix1 = NULL, **matrix2 = NULL, **res_matrix = NULL;
    int n1, m1, n2, m2;
    int rc = OK;

    if (argc != 4 && argc != 5)
    {
        printf("app.exe action mtr_1.txt [mtr_2.txt] res.txt\n");
        rc = ERR_ARGS;
    }
    else
    {
        if (strcmp(argv[1], "h") == 0)
        {
            print_inf();
            rc = OK;
        }
        else
        {
            if (argc == 4 && strcmp(argv[1], "o") == 0)
            {
                rc = read_matrix(argv[2], &matrix1, &n1, &m1);
                if (rc != OK)
                    printf("Error code: %d\n", rc);
                else
                {
                    if (n1 != m1)
                    {
                        printf("Can't inverse this matrix\n");
                        rc = ERR_PARAM;
                    }
                    else
                    {
                        rc = inverse(matrix1, &res_matrix, n1);
                        if (rc != OK)
                            printf("Error code: %d\n", rc);
                        else
                        {
                            rc = print_matrix_to_file(argv[3], res_matrix, n1, n1);
                            free_matrix(res_matrix, n1);
                            if (rc != OK)
                                printf("Error code: %d\n", rc);
                        }
                    }
                    free_matrix(matrix1, n1);
                }
            }
            else
            {
                if (argc == 5 && (strcmp(argv[1], "a") == 0 || strcmp(argv[1], "m") == 0))
                {
                    rc = read_matrix(argv[2], &matrix1, &n1, &m1);
                    if (rc != OK)
                        printf("Error code: %d\n", rc);
                    else
                    {
                        rc = read_matrix(argv[3], &matrix2, &n2, &m2);
                        if (rc != OK)
                            printf("Error code: %d\n", rc);
                        else
                        {
                            if (strcmp(argv[1], "a") == 0)
                            {
                                if (n1 != n2 || m1 != m2)
                                {
                                    printf("Can't get addiction\n");
                                    rc = ERR_PARAM;
                                }
                                else
                                {
                                    res_matrix = addition(matrix1, matrix2, n1, m1);
                                    if (!res_matrix)
                                    {
                                        printf("Error code: 3\n");
                                        rc = ERR_MEM;
                                    }
                                    else
                                    {
                                        rc = print_matrix_to_file(argv[4], res_matrix, n1, m1);
                                        free_matrix(res_matrix, n1);
                                        if (rc != OK)
                                            printf("Error code: %d\n", rc);
                                    }
                                }
                            }
                            if (strcmp(argv[1], "m") == 0)
                            {
                                if (m1 != n2)
                                {
                                    printf("Can't get multiplication\n");
                                    rc = ERR_PARAM;
                                }
                                else
                                {
                                    res_matrix = multiplication(matrix1, matrix2, n1, m1, m2);
                                    if (!res_matrix)
                                    {
                                        printf("Error code: 3\n");
                                        rc = ERR_MEM;
                                    }
                                    rc = print_matrix_to_file(argv[4], res_matrix, n1, m2);
                                    free_matrix(res_matrix, n1);
                                    if (rc != OK)
                                        printf("Error code: %d\n", rc);
                                }
                            }
                            free_matrix(matrix2, n2);
                        }
                        free_matrix(matrix1, n1);
                    }
                }
                else
                {
                    printf("Error code: 1");
                    rc = ERR_ARGS;
                }
            }
        }
    }
    
    return rc;
}
