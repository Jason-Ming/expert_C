#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

 
int g_iSeq=0;
 
void SignHandlerNew(int iSignNo,siginfo_t *pInfo,void *pReserved)
{
    int iSeq=g_iSeq++; 
    printf("%d Enter SignHandlerNew,signo:%d.",iSeq,iSignNo); 
    sleep(3); 
    printf("%d Leave SignHandlerNew,signo:%d.",iSeq,iSignNo); 
}
 
int main()
{
    char szBuf[8]; 
    int iRet; 
    struct sigaction act; 
    act.sa_sigaction=SignHandlerNew; 
    act.sa_flags=SA_SIGINFO; 
              // 
    sigemptyset(&act.sa_mask); 
   sigaction(SIGINT,&act,NULL); 
    sigaction(SIGQUIT,&act,NULL); 
    do{ 
        iRet=read(STDIN_FILENO,szBuf,sizeof(szBuf)-1); 
        if(iRet<0){ 
            perror("read fail."); 
            break; 
        } 
        szBuf[iRet]=0; 
        printf("Get: %s",szBuf); 
    }while(strcmp(szBuf,"quit ")!=0); 
    return 0; 
}

