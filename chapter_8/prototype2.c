#include <stdio.h>
#include "printmem.h"

int olddef(float d, char i);

void printInt(void *addr)
{
    printf("int: %d %x\n", *(int*)(addr), *(int*)(addr));
}

main()
{
    float d = 10.0;
    char i = 3;

    printMem(&d,sizeof(d));
    printMem(&i,sizeof(i));

    printInt(&d);
    
    olddef(d, i);

    newdef(d, i);
}

