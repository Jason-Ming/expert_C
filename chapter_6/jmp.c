#include <setjmp.h>
#include <stdio.h>
jmp_buf buf;

void banana()
{
	printf("in banana() \n");
	longjmp(buf, 0);

	/* 以下代码不会被执行 */
	printf("you will never see this, because i longjmp'd");
}

set

