#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"

int alarm_flag=FALSE;

/* SIGALRM ������*/
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

    /*  �趨 SIGALRM �Ĺ�������*/
    signal(SIGALRM,setflag);

    /*  �趨��ʱ��*/
    alarm(nsecs);

    /* ʹ�� pause()���õȴ��ź�, �źŴ�����֮��ֱ��ִ��PAUSE�������� */
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

