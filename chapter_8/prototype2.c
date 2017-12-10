#include <stdio.h>
#include "printmem.h"
#include "prototype1.h"

int olddef(int x, float d, char i);

void printInt(void *addr)
{
    printf("int: %d %x\n", *(int*)(addr), *(int*)(addr));
}

main()
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
    //olddef(x, d, i);

    /* newdef没有声明原型，编译器按照K&R C 的方式传递，即先进行类型升级再压栈，
    压栈的次序是从最后一个参数开始，先压4个字节的i，再压8个字节的double，再压4个字节的x*/
    /* 但是newdef的定义是按照新的ANSI C 定义的，所以在读参数的时候是从第一个参数开始读的*/
    newdef(x, d, i, y);
}

