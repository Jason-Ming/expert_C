#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	int c;

	/* 终端驱动处于普通的一次一行模式 */

	/* raw 选项会忽略int和stop信号处理，这里的忽略是终端ctrl按键失效，但是其他进程发信号还是可以处理的 */
	/* 每一个字符都会触发getchar调用 包括回车'\r' */
	system("stty raw");

	/* 现在终端驱动处于的一次一字模式 */
	c = getchar();
	printf("%d", c);

	//此时的pause是不会因为按ctrl+C唤醒的
	//pause();

	//system("pause");

	c = getchar();

	printf("after %d", c);
	
	//system("pause");
	
	/* 驱动又回到一次一行模式 */
	system("stty cooked");
	
	return 0;
}

