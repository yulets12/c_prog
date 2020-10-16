#include <stdio.h>

int main(void)
{
    setbuf(stdout, NULL);
    double v1, v2, t1, t2, t, v;

    printf("Input v1, t1, v2, t2: ");
    scanf("%lf%lf%lf%lf", &v1, &t1, &v2, &t2);

    v = v1 + v2;
    t = (v1 * t1 + v2 * t2) / v;

    printf("Volume is %lf\n", v);
    printf("Temperature is %lf\n", t);

    return 0;
}
