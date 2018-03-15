#include <stdio.h>
#include <time.h>
#include <limits.h>

/* this is the main function! */

void print_tm(struct tm *ptm)
{
	if(ptm == NULL)
	{
		printf("	print tm: null\n");
		return;
	}
	printf("	print tm:\n");
	printf("		year  : %d\n", ptm->tm_year);
	printf("		month : %d\n", ptm->tm_mon);
	printf("		day   : %d\n", ptm->tm_mday);
	printf("		hour  : %d\n", ptm->tm_hour);
	printf("		minute: %d\n", ptm->tm_min);
	printf("		second: %d\n", ptm->tm_sec);
}

void print_diff(time_t t, time_t current)
{
	double diff  = difftime(t, current);
    double minutes = diff/60;
    double hours = minutes/60;
    double days = hours/24;
    double weeks = days/7;
    double months = days/30;
    double years = days/365;
    
    printf("	diff time: (%0.f)seconds = \n"
		"			%f years, \n"
		"			%f months, \n"
		"			%f weeks, \n"
		"			%f days, \n"
		"			%f hours, \n"
		"			%f minutes \n", 
        diff, years, months, weeks, days, hours, minutes);
}

void print_time(char *s, time_t t)
{
	printf("=====BEGIN=====----------------------------------------------------------------\n");
	print_diff(t, 0);
	//%lx���������long��ʮ�����Ʊ�ʾ��%llx��%Lx��ʾlonglong��ʮ�����Ʊ�ʾ
	printf("	    %s = %ld, %lX, %s \n", s, t, t, ctime(&t));
	print_tm(gmtime(&t));
	printf("	gmt %s = %ld, %lX, %s \n", s, t, t, asctime(gmtime(&t)));
	printf("=====END=======----------------------------------------------------------------\n");	
}

int main()
{
	//ʵ�ʵ�64��32λ���У����ֵ����0x7FFFFFFF
    printf("INT_MAX = %X, %d\n", INT_MAX, INT_MAX);

	//time_t һ����time.hͷ�ļ��ж���Ϊlong, ��32λ������32λ, ��64λ������64λ
	
	//time_t��ʾ���ڱ�׼ʱ��1970��1��1��0ʱ0��0�뵽���ڵ�������
	//���κ�ʱ���ڣ����ֵ����һ���ġ�
	
	//ctime��ӡ��ǰ��ʱ�䣬�Ǵ�ʱ����,ʹ��gmt��ȡ����ʱ�䣬��0ʱ��
	
	//ctime�ǽ�time_tת��Ϊ������ʾ��ʱ��,
	time_t current_time = time(&current_time);
	print_time("current time", current_time);

#ifdef __i386__
	
	//���£����Կ�������32λϵͳ�У����Ա�ʾ1970��ǰ���Լ68�����ҵ�ʱ������
	print_time("biggest", 0x7FFFFFFF);

	print_time("zero", 0);

	print_time("smallest", 0x80000000);

#endif

#ifdef __x86_64__

	//��64λϵͳ�У��������ܱ�ʾ0x8000000000000000~0x7FFFFFFFFFFFFFFF��ʱ���
	print_time("biggest", 0x7FFFFFFFFFFFFFFF);

	print_time("zero", 0);
	
	print_time("smallest", 0x8000000000000000);


	//������Ϊctime/asctime������ʾ��������ֵΪ32λ�з������������ֵ��0x7FFFFFFF,
	//��ô������������ֵΪ0x7FFFFFFF��12��31��23ʱ59��59��
	
	//�������۵�gmt�ĸ���ֵ�ͼ��趼���ڶ��������׼ʱ�䣬����ʱ����������ֵ��
	//����ʱ��Ҫ��ȥʱ������ΪUTCʱ��Ҫ���ڱ���ʱ��

	struct tm biggest_tm;
	biggest_tm.tm_year = 0x7FFFFFFF - 1900;//int ����
	biggest_tm.tm_mon = 11;
	biggest_tm.tm_mday = 31;
	biggest_tm.tm_hour = 23;
	biggest_tm.tm_min = 59;
	biggest_tm.tm_sec = 59;

	//mktime������������ָ��tm�ṹ����ת���ɴӹ�Ԫ1970��1��1��0ʱ0��0 �����������UTCʱ����������������
	//��������ת��ΪUTCʱ������1970��1��1��0ʱ0��0�����
	time_t biggest = mktime(&biggest_tm);

	print_time("biggest", biggest);
	

	//��СֵΪ0x80000000��1��1��0ʱ0��0�룬����С��1900���ʱ��
	//������Ȼ����ʾ��ʽ����ʱ�䣬��gmtime(&t)��ֵ��������⣬��t���Ĳ�����������ʱ��
	//����ʱ��Ϊ��С��t������������ʱ����ʱ��
	struct tm smallest_tm;
	smallest_tm.tm_year = 00;
	smallest_tm.tm_mon = 11;
	smallest_tm.tm_mday = 31;
	smallest_tm.tm_hour = 23;
	smallest_tm.tm_min = 54;
	smallest_tm.tm_sec = 17;
	time_t smallest = mktime(&smallest_tm);

	print_time("smallest", smallest);

	//��������gmtime(&t)�����⣬�Զ�����Ϊ�����8Сʱ5��43�룬��ô��С�ɸ�ʽ����ʾ��ֵΪ
	//����ʱ����ʱ��ֵ��ȷ����û������
	smallest_tm.tm_year = -0x80000000;
	smallest_tm.tm_mon = 0;
	smallest_tm.tm_mday = 1;
	smallest_tm.tm_hour = 8;
	smallest_tm.tm_min = 5;
	smallest_tm.tm_sec = 43;
	smallest = mktime(&smallest_tm);
	//smallest--;

	print_time("smallest", smallest);
#endif

    return 0;
}

