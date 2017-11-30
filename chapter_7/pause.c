#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"

int alarm_flag=FALSE;

/* SIGALRM 处理函数*/
void setflag(int signo)
{
    alarm_flag=TRUE;
}

void main(int argc,char* argv[])
{
    int nsecs;
    int i;

    if (argc<2)
    {
        fprintf(stderr,"Usage:tml #minutes message\n");
        exit(1);
    }

    if ((nsecs=atoi(argv[1]))<=0)
    {
        fprintf(stderr,"Invalid time\n");
        exit(2);
    }

    /*  设定 SIGALRM 的关联动作*/
    signal(SIGALRM,setflag);

    /*  设定定时器*/
    alarm(nsecs);

    /* 使用 pause()调用等待信号, 信号处理完之后直接执行PAUSE后面的语句 */
    pause();

    if (alarm_flag)
    {
        printf(BELLS);
        for (i=2;i<argc;i++)
        {
            printf("%s\n",argv[i]);
        }
    }
    exit(0);
}

