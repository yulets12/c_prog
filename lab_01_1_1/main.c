#include <stdio.h>
#include <math.h>
#define PI 3.14159265359

int main(void)
{
    setbuf(stdout, NULL);
    double osn1, osn2, angle, h, s;
    
    printf("Input smaller base of trapezium, larger base and angle(in degrees):\n");
    scanf("%lf%lf%lf", &osn1, &osn2, &angle);
    
    h = tan(angle * PI / 180.0) * (fabs(osn2 - osn1) / 2.0);
    s = h * (osn1 + osn2) / 2;
    
    printf("Square of trapezium is %lf\n", s);
    return 0;
}
