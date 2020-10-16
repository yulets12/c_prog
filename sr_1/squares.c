/*
Вычисляет площадь прямоугольника.
*/

#include <stdio.h>
#define PI 3.14

float sqofrec(float a, float b)
{
    return a*b;
}

float sqofcir(float r)
{
    return PI*r*r;
}

int main(void)
{
    float a,b,r,st,sr,sc;

    printf("Input a and b: ");
    scanf("%f%f",&a,&b);

    printf("Input r: ");
    scanf("%f",&r);
    sr=sqofrec(a,b);
    sc=sqofcir(r);
    st=sr+sc;
    printf("Square of rectangle is %8.3f\n",sr);
    printf("Square of circle is %8.3f\n",sc);
    printf("Square of all figures is %10.3f\n",st);
    return 0;
}
