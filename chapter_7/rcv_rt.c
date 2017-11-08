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
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = sighandler;

    if(sigaction(SIGRTMIN+5, &act, 0) == -1)
    {
        exit(-1);
    }

    pause();
    
    return 0;
}

