#include <setjmp.h>
#include <stdio.h>
jmp_buf buf;

void banana()
{
	printf("in banana() \n");
	longjmp(buf, 0);

	/* ���´��벻�ᱻִ�� */
	printf("you will never see this, because i longjmp'd");
}

void main()
{
	if(setjmp(buf))
	{
		printf("back in main\n");
	}
	else
	{
		printf("first time through\n");
		banana();
	}
}
