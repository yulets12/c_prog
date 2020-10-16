#include <stdio.h>
#define FLAT_NUM 4
#define FLOOR_NUM 9
#define N (FLAT_NUM * FLOOR_NUM)

int main(void)
{
    setbuf(stdout, NULL);
    int flat, floor, porch;

    printf("Input the number of the flat: ");
    scanf("%d", &flat);

    porch = flat / N + (flat % N > 0);
    floor = flat / FLAT_NUM + (flat % FLAT_NUM > 0) - (porch - 1) * FLOOR_NUM;

    printf("Porch number is %d\nFloor number is %d", porch, floor);

    return 0;
}
