#include <curses.h>

#include <sys/ioctl.h>


int kbhit(void)
{
	int i = 0;

	if(ioctl(0, FIONREAD, &i) < 0)
	{
		perror("errno:");
	}
	
	if(i)
	{
		//这个打印会使第二个mvprintw显示异常
		//printf("kbhit %d\n", i);
	}
	
	return i;
}


int main()
{
	int c = ' ';
	int i = 0;

	initscr();//初始化curses函数
	cbreak();//设置cbreak模式，字符一键入，直接传给程序
	noecho();//按键时不在屏幕上回显字符

	mvprintw(0, 0, "print 'q' to quit\n");
	refresh();

	while(c != 'q')
	{
		i++;
		if(kbhit() != 0)
		{
			c = getchar();//不会阻塞，因为我们知道有一个字符正在等待
			mvprintw(1, 0, "got char '%c' on iteration %d \n", c, i);
			refresh();
		}
	}

	nocbreak();
	echo();//用于关闭键盘输入字符的回显
	endwin();//结束curses
	return 0;
	
}

