#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int g_Seq=0;
 
void signalHandlerNew(int iSigNo, siginfo_t *pInfo, void *pReserved)
{
    int seq = g_Seq++; 
    int ret = 0;
    
    //输出不加上回车，会放在缓冲区中，直到下次触发清缓冲区
    printf("%d Enter signalHandlerNew,signo:%d.\n", seq, iSigNo); 


    //和调用系统调用没有关系，信号会被其他类型的信号中断
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

    /* SA_RESTART 缺少这个掩码，会导致信号处理之后read失败,而signal方式则是成功的 */
    /* SA_NODEFER 这个掩码会使信号的处理可以被中断，不管是相同类型的信号还是不同类型的信号 */
    /*            如果不加这个掩码，就和signal的处理一样的，相同信号的会屏蔽，但是不同信号的会中断，但是只能中断一次  */
    act.sa_flags = SA_SIGINFO | SA_RESTART;// | SA_NODEFER;
    
    sigemptyset(&act.sa_mask); 
    sigaddset(&act.sa_mask,SIGQUIT); /* 使SIGINT不能被SIGQUIT中断,且SIGQUIT不能被自身中断 */

    sigaction(SIGINT,&act,NULL); 
    sigaction(SIGQUIT,&act,NULL); 

    do
    {
        //若输入字符后不输入回车，输入ctrl+C会产生信号，处理完信号后会清空缓冲区
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

