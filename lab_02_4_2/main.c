#include <stdio.h>
#include <math.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define EPS 0.0000001
#define IN 1
#define OUT 0

float length(float xm, float ym, float xk, float yk)
{
    return sqrt((xm - xk) * (xm - xk) + (ym - yk) * (ym - yk));
}

int solve(float xa, float ya, float xb, float yb, float xn, float yn)
{
    float ab = length(xa, ya, xb, yb);
    float an = length(xa, ya, xn, yn);
    float bn = length(xb, yb, xn, yn);

    if (fabs(an + bn - ab) < EPS)
    {
        return IN;
    }
    else
    {
        return OUT;
    }
}

int main(void)
{
    float xa, ya, xb, yb, xn, yn;
    int q, rc = OK;

    printf("AB is a segment, N is a point.\n");
    printf("Input xa, ya, xb, yb, xn, yn ((xa != xb) || (ya != yb)): ");
    if (scanf("%f%f%f%f%f%f", &xa, &ya, &xb, &yb, &xn, &yn) == 6)
    {
        if ((xa != xb) || (ya != yb))
        {
            q = solve(xa, ya, xb, yb, xn, yn);
            if (q == IN)
            {
                printf("The point is on the segment.\n");
                printf("%d", q);
            }
            else
            {
                printf("The point is not on the segment.\n");
                printf("%d", q);
            }
        }
        else
        {
            printf("(xa != xb) || (ya != yb) !!!");
            rc = ERR_RANGE;
        }
    }
    else
    {
        printf("All the meanings must be float!");
        rc = ERR_IO;
    }
    return rc;
}
