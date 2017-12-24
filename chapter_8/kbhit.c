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

	/* 非阻塞方式，只有缓冲区中有字符的时候才getchar，这个等待过程中在for循环中可以做其他的事情,
	   实际打印的iteration的值增长的很快, 说明的在没有敲击键盘的时候，for循环了很多次 */
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

