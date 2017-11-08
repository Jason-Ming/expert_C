#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


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
    if(signal(SIGRTMIN+5, fun1) == SIG_ERR)
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

