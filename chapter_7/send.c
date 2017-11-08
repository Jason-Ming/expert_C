#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char** argv)
{
    pid_t pid = (pid_t)atol(argv[1]);
    printf("send to pid: %d.\n",pid);
    
    for(int i = 0; i<500; ++i)
    {
        //sleep(1);
        kill(pid, SIGRTMIN+5);
    }
}

