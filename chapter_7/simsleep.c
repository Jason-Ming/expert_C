#include <signal.h>
#include <stdio.h>
#include <unistd.h>
 
void SignHandler(int iSignNo)
{
    printf("signal:%d \n",iSignNo); 
}

/* ע�⣺��Ϊsleep���ڲ�����alarmʵ�ֵģ������ڳ�������ò�Ҫsleep��alarm���ã�������ɻ��ҡ� */
/* ��Ҳ������Ϊʲôsleep���Ա��жϣ���Ϊ��ʹ����pause���ȴ�alarm�źţ�
   ��������������ź����ˣ�pause�ͽ����ˣ�����ִ���źŴ�������֮��sleep�ͽ����ˡ� */
int main()
{
    signal(SIGALRM,SignHandler); 
    alarm(3); 
    printf("Before pause().\n"); 
    pause(); 
    printf("After pause().\n"); 
    return 0; 
}

