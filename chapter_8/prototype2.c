#include <stdio.h>
#include "printmem.h"
#include "prototype1.h"

int olddef();

void printInt(void *addr)
{
    printf("int: %d %x\n", *(int*)(addr), *(int*)(addr));
}

void main()
{
    int x = 0x12345678;
    float d = 10.0;
    char i = 3;
    int y = 0x9abcdef0;
    //printMem(&d,sizeof(d));
    //printMem(&i-3,4);

    //printInt(&d);

    //printf("-----------------------------------------------------\n");

    //printMem(&d,sizeof(d));
    //printMem(&i-3,4);
    olddef(x, d, i);

    /* newdef没有声明原型，编译器按照K&R C 的方式传递，即先进行类型升级再压栈，
    但是newdef的定义是按照新的ANSI C 定义的，所以在读参数的时候是实际的值开始读的*/
    newdef(x, d, i, y);
}

