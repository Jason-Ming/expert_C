#include <stdio.h>
#include "printmem.h"
void printMem(void *addr, int len)
{
    printf("start addr: %p ------------------------------------------------\n", addr);
    
    for(int i = 0; i < len; i++)
    {
        printf("addr: %p: %x \n", addr + i, *(char*)(addr+i));
    }
}

void printmem(char *p, int length)
{
    for(int j = 0; j < length; j++)
    {
        printf("%p: 0x%x\n", p+j, p[j]);
    }
}

