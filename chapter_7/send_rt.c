#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char* argv[])
{
    char data[] = "helloworld";
    
    printf("Send process pid = %d.\n", getpid());

    union sigval value;
    //value.sival_int = 12345678;

    //��ͬ���̿ռ䣬�ڴ治���Թ���
    value.sival_ptr = data;
    pid_t pid = (pid_t)atoi(argv[1]);
    sigqueue(pid, SIGINT, value);
    
    return 0;
}

