#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int sequence[128] = {0};

int g_Seq = 0;

#define DUMPCOPY for(int i = 0; i < 65536; i++)\
destination[i] = source[i];


void signalHandler(int iSigNo)
{
    int seq = g_Seq; 
    int ret = 0;
    
    //��������ϻس�������ڻ������У�ֱ���´δ����建����
    //printf("%d Enter SignHandler,signo:%d.\n", seq, iSigNo); 
    sequence[g_Seq++] = iSigNo;
    char source[65536], destination[65536];
    int i, j;
    for(j = 0; j < 10000; j++)
    {
        DUMPCOPY;
    }
    sequence[g_Seq++] = iSigNo;

    //�͵���ϵͳ����û�й�ϵ���źŻᱻ�������͵��ź��ж�
    //ret = sleep(3); 
    //printf("%d Leave SignHandler,signo:%d. sleepRet: %d.\n", seq, iSigNo, ret); 
}

void printSequence()
{
    for(int i = 0; i < 128; i++)
    {
        if(i % 16 == 0)
        {
            printf("\n");
        }
        printf("%2d ", sequence[i]);
    }

    printf("\n");
}

int main(void)
{
    char buf[8];
    int ret;

    int compareRet = 0;

    //�Ʋ�: �ڰ��¶�Ӧ��ctrl+C ����ctrl+\ʱ���źžͻ����
    signal(SIGINT, signalHandler);
    signal(SIGQUIT, signalHandler);
    //signal(SIGTSTP, signalHandler);

    do
    {
        //�������ַ�������س�������ctrl+C������źţ��������źź����ջ�����
        ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
        if(ret<0)
        {
            printf("read fail.\n"); 
            break; 
        }
        else
        {
            printf("ret: %d.\n", ret);
        }
        
        buf[ret == 0 ? 0 : ret - 1] = '\0';

        printf("Get: %s, %d.\n", buf, strlen(buf));
        
        compareRet = strcmp(buf, "quit");

        printf("Compare: %d.\n", compareRet);

        printSequence();
    }
    while(compareRet != 0);
    
    return 0;
}

