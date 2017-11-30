#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    pid_t pid = (pid_t)atol(argv[1]);
    printf("send to pid: %d.\n",pid);
    
    for(int i = 0; i<5000; ++i)
    {
        //usleep(1);
        kill(pid, SIGINT);
    }
}

