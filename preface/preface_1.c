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
	//%lx输出长整型long的十六进制表示，%llx和%Lx表示longlong的十六进制表示
	printf("	    %s = %ld, %lX, %s \n", s, t, t, ctime(&t));
	print_tm(gmtime(&t));
	printf("	gmt %s = %ld, %lX, %s \n", s, t, t, asctime(gmtime(&t)));
	printf("=====END=======----------------------------------------------------------------\n");	
}

int main()
{
	//实际的64和32位机中，这个值都是0x7FFFFFFF
    printf("INT_MAX = %X, %d\n", INT_MAX, INT_MAX);

	//time_t 一般在time.h头文件中定义为long, 在32位机中是32位, 在64位机中是64位
	
	//打印当前的时间，使用time获取的时间是带时区的,使用gmt获取世界时间
	//ctime是将time_t转换为可以显示的时间,
	time_t current_time = time(&current_time);
	print_time("current time", current_time);

#ifdef __i386__
	
	//以下，可以看出，在32位系统中，可以表示1970年前后大约68年左右的时间区域
	print_time("biggest", 0x7FFFFFFF);

	print_time("zero", 0);

	print_time("smallest", 0x80000000);

#endif

#ifdef __x86_64__

	//在64位系统中，理论上能表示0x8000000000000000~0x7FFFFFFFFFFFFFFF的时间段
	print_time("biggest", 0x7FFFFFFFFFFFFFFF);

	print_time("zero", 0);
	
	print_time("smallest", 0x8000000000000000);


	//但是因为ctime它能显示的年的最大值为32位有符号整数的最大值即0x7FFFFFFF,
	//那么其能输入的最大值为0x7FFFFFFF年12月31日23时59分59秒
	//最小值为0x80000000年1月1日0时0分0秒

	struct tm biggest_tm;
	biggest_tm.tm_year = 0x7FFFFFFF - 1900;
	biggest_tm.tm_mon = 11;
	biggest_tm.tm_mday = 31;
	biggest_tm.tm_hour = 23;
	biggest_tm.tm_min = 59;
	biggest_tm.tm_sec = 59;
	time_t biggest = mktime(&biggest_tm);

	print_time("biggest", biggest);
	

	struct tm smallest_tm;
	smallest_tm.tm_year = 01;
	smallest_tm.tm_mon = 0;
	smallest_tm.tm_mday = 1;
	smallest_tm.tm_hour = 0;
	smallest_tm.tm_min = 0;
	smallest_tm.tm_sec = 0;
	time_t smallest = mktime(&smallest_tm);
	smallest-=300;

	print_time("smallest", smallest);
#endif

    return 0;
}

