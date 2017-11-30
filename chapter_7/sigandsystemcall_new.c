#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int g_Seq=0;
 
void signalHandlerNew(int iSigNo, siginfo_t *pInfo, void *pReserved)
{
    int seq = g_Seq++; 
    int ret = 0;
    
    //��������ϻس�������ڻ������У�ֱ���´δ����建����
    printf("%d Enter signalHandlerNew,signo:%d.\n", seq, iSigNo); 


    //�͵���ϵͳ����û�й�ϵ���źŻᱻ�������͵��ź��ж�
    ret = sleep(3);
    
    printf("%d Leave signalHandlerNew,signo:%d. sleepRet: %d.\n", seq, iSigNo, ret); 
}


int main()
{
    char buf[8]; 
    int ret; 
    int compareRet = 0;
    
    struct sigaction act; 
    act.sa_sigaction = signalHandlerNew; 

    /* SA_RESTART ȱ��������룬�ᵼ���źŴ���֮��readʧ��,��signal��ʽ���ǳɹ��� */
    /* SA_NODEFER ��������ʹ�źŵĴ�����Ա��жϣ���������ͬ���͵��źŻ��ǲ�ͬ���͵��ź� */
    /*            �������������룬�ͺ�signal�Ĵ���һ���ģ���ͬ�źŵĻ����Σ����ǲ�ͬ�źŵĻ��жϣ�����ֻ���ж�һ��  */
    act.sa_flags = SA_SIGINFO | SA_RESTART;// | SA_NODEFER;
    
    sigemptyset(&act.sa_mask); 
    sigaddset(&act.sa_mask,SIGQUIT); /* ʹSIGINT���ܱ�SIGQUIT�ж�,��SIGQUIT���ܱ������ж� */

    sigaction(SIGINT,&act,NULL); 
    sigaction(SIGQUIT,&act,NULL); 

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

    }
    while(compareRet != 0);
    
    return 0; 
}

