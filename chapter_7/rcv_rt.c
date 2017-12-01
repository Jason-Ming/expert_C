#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sendSigToSelf()
{
    char data[] = "helloworld";
    
    printf("Send to process pid = %d.\n", getpid());

    union sigval value;
    //value.sival_int = 12345678;

    //��ͬ�Ľ��̿ռ䣬�ڴ���Թ���
    value.sival_ptr = data;
    pid_t pid = getpid();
    sigqueue(pid, SIGINT, value);    
}

void sighandler(int sig, siginfo_t *info, void *context)
{
    //printf("Send process id: %d, receive sig: %s, data: %d.\n", 
        //info->si_pid, strsignal(sig), info->si_value.sival_int);
    printf("Send process id: %d, receive sig: %s, data: %s.\n", 
        info->si_pid, strsignal(sig), (char *)info->si_value.sival_ptr);
}

void sigSegvHandler(int sig)
{
    printf("catch Segmentation fault!\n");
}

int main()
{
    printf("pid = %d.\n", getpid());

    struct sigaction act;
    act.sa_flags = SA_SIGINFO;/* ʹ���µĽṹ */
    sigemptyset(&act.sa_mask);/* �����κ��ź����� */
    act.sa_sigaction = sighandler;

    signal(SIGSEGV, sigSegvHandler);
    
    if(sigaction(SIGINT, &act, 0) == -1)
    {
        exit(-1);
    }

    sendSigToSelf();
    
    pause();
    
    return 0;
}

