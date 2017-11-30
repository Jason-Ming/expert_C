#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sighandler(int sig, siginfo_t *info, void *context)
{
    printf("Send process id: %d, receive sig: %s, data: %d.\n", info->si_pid, strsignal(sig), info->si_value.sival_int);
}


int main()
{
    printf("pid = %d.\n", getpid());

    struct sigaction act;
    act.sa_flags = SA_SIGINFO;/* 使用新的结构 */
    sigemptyset(&act.sa_mask);/* 不对任何信号阻塞 */
    act.sa_sigaction = sighandler;

    if(sigaction(SIGINT, &act, 0) == -1)
    {
        exit(-1);
    }

    pause();
    
    return 0;
}

