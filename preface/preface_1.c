#include <stdio.h>
#include <time.h>
#include <limits.h>

/* this is the main function! */

void print_tm(struct tm *ptm)
{
	if(ptm == NULL)
	{
		printf("print tm: null\n");
		return;
	}
	printf("print tm:\n");
	printf("year  : %d\n", ptm->tm_year);
	printf("month : %d\n", ptm->tm_mon);
	printf("day   : %d\n", ptm->tm_mday);
	printf("hour  : %d\n", ptm->tm_hour);
	printf("minute: %d\n", ptm->tm_min);
	printf("second: %d\n", ptm->tm_sec);
}

int main()
{
	//ʵ�ʵ�64��32λ���У����ֵ����0x7FFFFFFF
    printf("INT_MAX = %X, %d\n", INT_MAX, INT_MAX);

	//time_t һ����time.hͷ�ļ��ж���Ϊlong, ��32λ������32λ, ��64λ������64λ
	
	//��ӡ��ǰ��ʱ�䣬ʹ��time��ȡ��ʱ���Ǵ�ʱ����,ʹ��gmt��ȡ����ʱ��
	//ctime�ǽ�time_tת��Ϊ������ʾ��ʱ��,
    time_t current_time = time(&current_time);
    printf("current time = %s \n", ctime(&current_time));
	printf("current asctime = %s \n", asctime(gmtime(&current_time)));

#ifdef __i386__
	
	//���£����Կ�������32λϵͳ�У����Ա�ʾ1970��ǰ���Լ68�����ҵ�ʱ������
    time_t biggest = 0x7FFFFFFF;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	print_tm(gmtime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));

	time_t zero = 0;

	printf("zero = %ld, %s \n", zero, ctime(&zero));
	print_tm(gmtime(&zero));
	printf("zero = %ld, %s \n", zero, asctime(gmtime(&zero)));

	time_t smallest = 0x80000000;

	printf("smallest = %ld, %s \n", smallest, ctime(&smallest));
	print_tm(gmtime(&smallest));
	printf("smallest = %ld, %s \n", smallest, asctime(gmtime(&smallest)));
#endif

#ifdef __x86_64__

	//��64λϵͳ�У��������ܱ�ʾ0x8000000000000000~0x7FFFFFFFFFFFFFFF��ʱ���
	time_t biggest = 0x7FFFFFFFFFFFFFFF;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	print_tm(gmtime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));

	time_t zero = 0;

	printf("zero = %ld, %s \n", zero, ctime(&zero));
	print_tm(gmtime(&zero));
	printf("zero = %ld, %s \n", zero, asctime(gmtime(&zero)));

	time_t smallest = 0x8000000000000000;

	printf("smallest = %ld, %s \n", smallest, ctime(&smallest));
	print_tm(gmtime(&smallest));
	printf("smallest = %ld, %s \n", smallest, asctime(gmtime(&smallest)));

	//������Ϊctime������ʾ��������ֵΪ32λ�з������������ֵ��0x7FFFFFFF,
	//��ô������������ֵΪ0x7FFFFFFF��12��31��23ʱ59��59��
	//��СֵΪ0x80000000��1��1��0ʱ0��0��

	struct tm biggest_tm;
	biggest_tm.tm_year = 0x7FFFFFFF - 1900;
	biggest_tm.tm_mon = 11;
	biggest_tm.tm_mday = 31;
	biggest_tm.tm_hour = 23;
	biggest_tm.tm_min = 59;
	biggest_tm.tm_sec = 59;
	biggest = mktime(&biggest_tm);

	biggest;
	
	//%lx���������long��ʮ�����Ʊ�ʾ��%llx��%Lx��ʾlonglong��ʮ�����Ʊ�ʾ
	printf("biggest = %ld, %lX, %s \n", biggest, biggest, ctime(&biggest));
	
	print_tm(gmtime(&biggest));
	printf("biggest = %ld, %lX, %s \n", biggest, biggest, asctime(gmtime(&biggest)));

	struct tm smallest_tm;
	smallest_tm.tm_year = 1;
	smallest_tm.tm_mon = 0;
	smallest_tm.tm_mday = 1;
	smallest_tm.tm_hour = 0;
	smallest_tm.tm_min = 0;
	smallest_tm.tm_sec = 0;
	smallest = mktime(&smallest_tm);
	
	//%lx���������long��ʮ�����Ʊ�ʾ��%llx��%Lx��ʾlonglong��ʮ�����Ʊ�ʾ
	printf("smallest = %ld, %lX, %s \n", smallest, smallest, ctime(&smallest));
	print_tm(gmtime(&smallest));
	printf("smallest = %ld, %lX, %s \n", smallest, smallest, asctime(gmtime(&smallest)));
#endif

    
    double diff  = difftime(biggest, current_time);
    double minutes = diff/60;
    double hours = minutes/60;
    double days = hours/24;
    double weeks = days/7;
    double months = days/30;
    double years = days/365;
    
    printf("diff time(%0.f)seconds = %f years, %f months, %f weeks, %f days, %f hours, %f minutes \n", 
        diff, years, months, weeks, days, hours, minutes);
    
    return 0;
}

