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

    //如果不退出，那么就会不停的定时的接收到信号
    //exit(1);

    //重新设置信号默认处理
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

