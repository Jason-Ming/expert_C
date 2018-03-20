#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>

/* this is the main function! */

void print_tm(struct tm *ptm)
{
	if(ptm == NULL)
	{
		printf("		print tm: null\n");
		return;
	}
	printf("		print tm:\n");
	printf("			year  : %d\n", ptm->tm_year);
	printf("			month : %d\n", ptm->tm_mon);
	printf("			day   : %d\n", ptm->tm_mday);
	printf("			hour  : %d\n", ptm->tm_hour);
	printf("			minute: %d\n", ptm->tm_min);
	printf("			second: %d\n", ptm->tm_sec);
	printf("			wday  : %d\n", ptm->tm_wday);
	printf("			yday  : %d\n", ptm->tm_yday);
	printf("			isdst : %d\n", ptm->tm_isdst);

	time_t t = mktime(ptm);
	printf("\n			seconds = %ld\n", t);

	//strftime() ������ʱ���ʽ��
	//���ǿ���ʹ��strftime����������ʱ���ʽ��Ϊ������Ҫ�ĸ�ʽ������ԭ�����£�
	//size_t strftime(
    // char *strDest,
    // size_t maxsize,
    // const char *format,
    // const struct tm *timeptr

	char tmpbuf[128];
   
	strftime( tmpbuf, 128, "\n		Date is %A, day %d of %B in the year %Y.\n", ptm);
    printf("%s", tmpbuf);

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

	//ctime�ǽ�time_tת��Ϊ������ʾ��ʱ���ַ���,�Ǵ�ʱ���ı���ʱ��
	//%lx���������long��ʮ�����Ʊ�ʾ��%llx��%Lx��ʾlonglong��ʮ�����Ʊ�ʾ
	printf("	>>>>	      %s = %ld, %lX, %s \n", s, t, t, ctime(&t));
	
	//asctime�ǽ�struct tmת��Ϊʱ���ַ��������ṹ�е�������Сʱ����ԭ����ʾ
	printf("	>>>>	  gmt %s = %ld, %lX, %s \n", s, t, t, asctime(gmtime(&t)));
	print_tm(gmtime(&t));
		
	printf("	>>>>	local %s = %ld, %lX, %s \n", s, t, t, asctime(localtime(&t)));
	print_tm(localtime(&t));

	printf("=====END=======----------------------------------------------------------------\n");	
}

int main()
{
	//ʵ�ʵ�64��32λ���У����ֵ����0x7FFFFFFF
    printf("INT_MAX = %X, %d\n", INT_MAX, INT_MAX);
	
	//UTCʱ�������ֱ�ʾ����:
	//(1)
	//time_t һ����time.hͷ�ļ��ж���Ϊlong, ��32λ������32λ, ��64λ������64λ
	//time_t ��ʾ���ڱ�׼ʱ��1970��1��1��0ʱ0��0�뵽���ڵ����������κ�ʱ���ڣ����ֵ����һ���ġ�
	//time_t time(time_t *t); ʹ��time��ȡ��ǰʱ���time_t

	time_t current_time = time(&current_time);
	print_time("current time", current_time);

	//(2)
	//struct tm�Ǵ洢��ʱ��Ľṹ
	//struct tm
	//{
	//    int tm_sec;  /*�룬������Χ0-59�� ��������61*/
	//    int tm_min;  /*���ӣ�0-59*/
	//    int tm_hour; /*Сʱ�� 0-23*/
	//    int tm_mday; /*�գ���һ�����еĵڼ��죬1-31*/
	//    int tm_mon;  /*�£� ��һ������0-11*/  1+p->tm_mon;
	//    int tm_year;  /*�꣬ ��1900�����Ѿ�������*/  1900�� p->tm_year;
	//    int tm_wday; /*���ڣ�һ���еĵڼ��죬 ������������0-6*/
	//    int tm_yday; /*�ӽ���1��1�յ�Ŀǰ����������Χ0-365*/
	//    int tm_isdst; /*�չ��Լʱ������*/
	//};
	//struct tm* gmtime(const time_t *timep);��time_t��ʾ��ʱ��ת��ΪUTCʱ�䣬
	//��һ��struct tm�ṹָ��,��0ʱ��
	//struct tm* localtime(const time_t *timep);
	//��gmtime���ƣ��������Ǿ���ʱ��ת����ʱ�䡣


	//(3)
	//struct timeval������ȷ��΢�
	//struct timeval
	//{
    //	long tv_sec; /*��*/
    //	long tv_usec; /*΢��*/
	//};
	//ʹ��int gettimeofday(struct timeval *tv, struct timezone *tz);
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	printf("current time: %ld seconds, %ld useconds.\n", tv.tv_sec, tv.tv_usec);

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
	biggest_tm.tm_year = 0x7FFFFFFF - 1900;//int ���ͣ���¼1900��֮�������
	biggest_tm.tm_mon = 11;
	biggest_tm.tm_mday = 31;
	biggest_tm.tm_hour = 23;
	biggest_tm.tm_min = 59;
	biggest_tm.tm_sec = 59;

	//mktime������������ָ��tm�ṹ����ת���ɴӹ�Ԫ1970��1��1��0ʱ0��0 �����������UTCʱ����������������
	//��Ȼ�õ�������������ô����˵�����������κεĵط����õ��Ľ������һ���ģ�Ҳ����˵�ú���������Ǳ���ʱ��
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

