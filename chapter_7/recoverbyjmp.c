#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

jmp_buf buf;

void handler(int s)
{
    if(s == SIGINT)
    {
        printf("now got a SIGINT signal!\n");
    }

    //只能执行一次，因为buf会被释放，再次执行会导致不可预知的情况，在这个程序中，handler不再被执行
    //longjmp(buf, 1);
}

void main()
{
    signal(SIGINT, handler);

    if(setjmp(buf))
    {
        printf("back in main!\n");
        goto loop;
        return;
    }
    else
    {
        //printf("first time through!\n");
    }

    loop:
        //printf("loop!\n");
        sleep(1);
        //signal(SIGINT, handler);
        raise(SIGINT);
        goto loop;
}

