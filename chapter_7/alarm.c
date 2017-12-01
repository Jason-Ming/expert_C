#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define TIMEOUT 5
#define MAXTRIES 5
#define LINESIZE 100
#define BELL '\007'
#define TRUE 1
#define FALSE 0

/*  判断超时是否已经发生的标志*/
static int time_out;
static char inputline[LINESIZE];
char* quickreply (char* prompt);

void main()
{
    printf("%s\n",quickreply("Input"));
}

/* SIGALRM 信号处理函数*/
void catch(int signo)
{
    /*  设定超时标志*/
    time_out=TRUE;

    /*  响铃警告*/
    putchar(BELL);
}

char* quickreply (char* prompt)
{
    int ntries;
    char* answer;
    void (*was)(int signo);
    
    /*  设定捕捉 SIGALRM 的的关联并保存原有关联*/
    was=signal(SIGALRM,catch);

    for (ntries=0;ntries<MAXTRIES;ntries++)
    {
        time_out=FALSE;
        printf("\n%s%d>",prompt, ntries);
        
        /*  设定定时器*/
        alarm(TIMEOUT);
        
        /*  获取输入*/
        /* 在等待输入期间，超过5秒中，会被信号中断，信号处理完之后，继续等待用户输入 */
        answer = fgets(inputline, sizeof(inputline), stdin);

        printf("anser: %s\n", answer);
        
        /*  关闭定时器*/
        alarm(0);
        
        if (!time_out)
        break;
    }
    
    /*  恢复原有的 SIGALRM 关联*/
    signal(SIGALRM,was);

    return (time_out?((char*) 0):answer);
}

