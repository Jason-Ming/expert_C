#include <stdio.h>
#include "printmem.h"
#include "prototype1.h"

int olddef(x, d, i)
int x;
float d;
char i;
{
    printMem(&x, 2*sizeof(int));
    printMem(&d, 2*sizeof(int));
    printMem(&i, 2*sizeof(int));

    printf("olddef: int = %x, float = %f, char = %x \n", x, d, i);
}

int newdef(int x, float d, float i, int y)
{
    printMem(&x, 8*sizeof(int));
    printMem(&d, 8*sizeof(int));
    printMem(&i, 8*sizeof(int));
    printMem(&y, 8*sizeof(int));

    printf("newdef: int = %x, float = %f, float = %f, int = %x \n", x, d, i, y);
}

