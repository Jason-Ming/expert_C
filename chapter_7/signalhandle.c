#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int s)
{
    switch(s)
    {
        case SIGBUS:
            printf("now got a bus error signal!\n");
            break;
        case SIGSEGV:
            printf("now got a segmentation violation signal!\n");
            break;
        case SIGILL:
            printf("now got an illegal instruction signal!\n");
            break;
    }

    //������˳�����ô�ͻ᲻ͣ�Ķ�ʱ�Ľ��յ��ź�
    //exit(1);

    //���������ź�Ĭ�ϴ���
    signal(s, SIG_DFL);
}

void main()
{
    int *p = NULL;
    signal(SIGBUS, handler);
    signal(SIGSEGV, handler);
    signal(SIGILL, handler);
    *p = 0;


}

