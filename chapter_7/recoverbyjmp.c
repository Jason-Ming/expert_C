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

    //ֻ��ִ��һ�Σ���Ϊbuf�ᱻ�ͷţ��ٴ�ִ�лᵼ�²���Ԥ֪�����������������У�handler���ٱ�ִ��
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

