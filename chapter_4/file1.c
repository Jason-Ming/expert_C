#include <stdio.h>

char s[4] = "abc";

int i[4] = {1,2,3,4};

void printmem(char *p, int length)
{
    for(int j = 0; j < length; j++)
    {
        printf("%p: 0x%x\n", p+j, p[j]);
    }
}

void ps()
{
    char *p = &s[0];
    printf("%p-%p\n", s, &s[0]);
    printmem(p,32);

    i[0] = (int)s;//i[0]为s的地址，s和i的内存是紧挨着的

    printmem(p,32);

    printf("%c-%c-%c-%c\n", s[0], s[1], s[2], s[3]);

    printmem(p,32);
}

