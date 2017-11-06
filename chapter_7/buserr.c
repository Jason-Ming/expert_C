#include <stdio.h>
union 
{
    char a[10];
    int i;
}u;

void printmem(char *p, int length)
{
    for(int j = 0; j < length; j++)
    {
        printf("%p: 0x%x\n", p+j, p[j]);
    }
}

void main()
{
    int *p = (int*)&(u.a[3]);
    *p = 0x12345678;

    printmem((char *)&u, sizeof(u));
}


