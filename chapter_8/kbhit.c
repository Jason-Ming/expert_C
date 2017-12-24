#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <asm-generic/errno-base.h>

int kbhit(void)
{
	int i = 0;

	if(ioctl(0, FIONREAD, &i) < 0)
	{
		perror("errno:");
		if(errno == EBADF)
		{
			printf("errno: bad file number");
		}
		if(errno == EINVAL)
		{
			printf("errno: invalid argument");
		}
	}
	
	if(i)
	{
		printf("kbhit %d\n", i);
	}
	
	return i;
}

void main(void)
{
	int i = 0;
	int c = ' ';

	system("stty raw -echo");

	printf("enter 'q' to quit \n");

	/* ��������ʽ��ֻ�л����������ַ���ʱ���getchar������ȴ���������forѭ���п���������������,
	   ʵ�ʴ�ӡ��iteration��ֵ�����ĺܿ�, ˵������û���û����̵�ʱ��forѭ���˺ܶ�� */
	for(; c != 'q'; i++)
	{
		if(kbhit() != 0)
		{
			c = getchar();
			printf("got %c, on iteration %d\n ", c, i);
		}
	}

	system(" stty cooked echo ");
}

