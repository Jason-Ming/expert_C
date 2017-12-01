#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define TIMEOUT 5
#define MAXTRIES 5
#define LINESIZE 100
#define BELL '\007'
#define TRUE 1
#define FALSE 0

/*  �жϳ�ʱ�Ƿ��Ѿ������ı�־*/
static int time_out;
static char inputline[LINESIZE];
char* quickreply (char* prompt);

void main()
{
    printf("%s\n",quickreply("Input"));
}

/* SIGALRM �źŴ�����*/
void catch(int signo)
{
    /*  �趨��ʱ��־*/
    time_out=TRUE;

    /*  ���徯��*/
    putchar(BELL);
}

char* quickreply (char* prompt)
{
    int ntries;
    char* answer;
    void (*was)(int signo);
    
    /*  �趨��׽ SIGALRM �ĵĹ���������ԭ�й���*/
    was=signal(SIGALRM,catch);

    for (ntries=0;ntries<MAXTRIES;ntries++)
    {
        time_out=FALSE;
        printf("\n%s%d>",prompt, ntries);
        
        /*  �趨��ʱ��*/
        alarm(TIMEOUT);
        
        /*  ��ȡ����*/
        /* �ڵȴ������ڼ䣬����5���У��ᱻ�ź��жϣ��źŴ�����֮�󣬼����ȴ��û����� */
        answer = fgets(inputline, sizeof(inputline), stdin);

        printf("anser: %s\n", answer);
        
        /*  �رն�ʱ��*/
        alarm(0);
        
        if (!time_out)
        break;
    }
    
    /*  �ָ�ԭ�е� SIGALRM ����*/
    signal(SIGALRM,was);

    return (time_out?((char*) 0):answer);
}

