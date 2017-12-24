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
		//�����ӡ��ʹ�ڶ���mvprintw��ʾ�쳣
		//printf("kbhit %d\n", i);
	}
	
	return i;
}


int main()
{
	int c = ' ';
	int i = 0;

	initscr();//��ʼ��curses����
	cbreak();//����cbreakģʽ���ַ�һ���룬ֱ�Ӵ�������
	noecho();//����ʱ������Ļ�ϻ����ַ�

	mvprintw(0, 0, "print 'q' to quit\n");
	refresh();

	while(c != 'q')
	{
		i++;
		if(kbhit() != 0)
		{
			c = getchar();//������������Ϊ����֪����һ���ַ����ڵȴ�
			mvprintw(1, 0, "got char '%c' on iteration %d \n", c, i);
			refresh();
		}
	}

	nocbreak();
	echo();//���ڹرռ��������ַ��Ļ���
	endwin();//����curses
	return 0;
	
}

