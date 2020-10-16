#include <stdio.h>
#include <math.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

float calc_s(float eps, float x)
{
    float el = 1.0;
    float sum = 0.0, mul = - x;
    int h1 = 2, h2 = 3;

    while (fabs(el) > eps)
    {
        sum += el;
        el = (h1 * h2 * mul) / 2;
        mul *= (- x);
        h1++;
        h2++;
    }
    return sum;
}

int main(void)
{
    int rc = OK;
    float eps, x, s, f, absol, compar;

    printf("Input x and eps: ");
    if (scanf("%f%f", &x, &eps) == 2)
    {
        if ((eps > 0) && (eps <= 1) && (fabs(x) < 1))
        {
            s = calc_s(eps, x);
            f = powf((1 + x), -3);
            absol = fabs(f - s);
            compar = absol / fabs(f);
            printf("%f %f %f %f", s, f, absol, compar);
        }
        else
        {
            rc = ERR_RANGE;
            printf("zero < eps <= one !!!\n|x| < one !!!");
        }
    }
    else
    {
        rc = ERR_IO;
        printf("Eps and x must be float!");
    }
    return rc;
}
