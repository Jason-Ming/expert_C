#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	int c;

	/* �ն�����������ͨ��һ��һ��ģʽ */

	/* raw ѡ������int��stop�źŴ�������ĺ������ն�ctrl����ʧЧ�������������̷��źŻ��ǿ��Դ���� */
	/* ÿһ���ַ����ᴥ��getchar���� �����س�'\r' */
	system("stty raw");

	/* �����ն��������ڵ�һ��һ��ģʽ */
	c = getchar();
	printf("%d", c);

	//��ʱ��pause�ǲ�����Ϊ��ctrl+C���ѵ�
	//pause();

	//system("pause");

	c = getchar();

	printf("after %d", c);
	
	//system("pause");
	
	/* �����ֻص�һ��һ��ģʽ */
	system("stty cooked");
	
	return 0;
}

