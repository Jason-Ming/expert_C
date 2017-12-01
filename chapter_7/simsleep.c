#include <signal.h>
#include <stdio.h>
#include <unistd.h>
 
void SignHandler(int iSignNo)
{
    printf("signal:%d \n",iSignNo); 
}

/* 注意：因为sleep在内部是用alarm实现的，所以在程序中最好不要sleep与alarm混用，以免造成混乱。 */
/* 这也解释了为什么sleep可以被中断，因为它使用了pause来等待alarm信号，
   但是如果有其他信号来了，pause就结束了，进而执行信号处理函数，之后sleep就结束了。 */
int main()
{
    signal(SIGALRM,SignHandler); 
    alarm(3); 
    printf("Before pause().\n"); 
    pause(); 
    printf("After pause().\n"); 
    return 0; 
}

