#include <stdio.h>
#include "printmem.h"

olddef(d, i)
float d;
char i;
{
    printMem(&d, 2*sizeof(int));
    printMem(&i, 2*sizeof(int));

    printf("olddef: float = %f, char = %x \n", d, i);
}

newdef(float d, char i)
{
    printMem(&d, 8*sizeof(int));
    printMem(&i, 8*sizeof(int));

    printf("newdef: float = %f, char = %x \n", d, i);
}

