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

    /* newdefû������ԭ�ͣ�����������K&R C �ķ�ʽ���ݣ����Ƚ�������������ѹջ��
    ����newdef�Ķ����ǰ����µ�ANSI C ����ģ������ڶ�������ʱ����ʵ�ʵ�ֵ��ʼ����*/
    newdef(x, d, i, y);
}

