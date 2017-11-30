#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 在send.c 发来的信号，这里只能处理部分，因为当处理信号的时候，部分信号被丢掉了 */
void fun(int sig)
{
    printf("Received a signal: %s.\n", strsignal(sig));
}

void fun1(int sig)
{
    static int count = 0;
    ++count;
    printf("Received a signal: %s. Total count = %d.\n", strsignal(sig), count);
}


int main()
{
    if(signal(SIGINT, fun1) == SIG_ERR)
    {
        perror("signal failed!\n");
    }

    printf("pid: %d.\n", getpid());

    while(1)
    {
        pause();
    }

    return 0;
}

