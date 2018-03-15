#include <stdio.h>
#include <time.h>
#include <limits.h>

/* this is the main function! */
int main()
{
	//实际的64和32位机中，这个值都是0x7FFFFFFF
    printf("INT_MAX = %X, %d\n", INT_MAX, INT_MAX);

	//time_t 一般在time.h头文件中定义为long, 在32位机中是32位, 在64位机中是64位
	
	//打印当前的时间，使用time获取的时间是带时区的,使用gmt获取世界时间
	//ctime是将time_t转换为可以显示的时间,
    time_t current_time = time(&current_time);
    printf("current time = %s \n", ctime(&current_time));
	printf("current asctime = %s \n", asctime(gmtime(&current_time)));

#ifdef __i386__
	
	//以下，可以看出，在32位系统中，可以表示1970年前后大约68年左右的时间区域
    time_t biggest = 0x7FFFFFFF;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));

	biggest = 0;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));

	biggest = 0x80000000;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));
#endif

#ifdef __x86_64__

	//在64位系统中，理论上能表示0x8000000000000000~0x7FFFFFFFFFFFFFFF的时间段
	biggest = 0x7FFFFFFFFFFFFFFF;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));

	biggest = 0;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));

	biggest = 0x8000000000000000;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));
	//但是因为ctime它能显示的年的最大值为32位有符号整数的最大值即0x7FFFFFFF,
	//那么其能输入的最大值为0x7FFFFFFF年12月31日23时59分59秒

	struct tm biggest_tm;
	biggest_tm.tm_year = 0x7FFFFFFF - 1900;
	biggest_tm.tm_mon = 11;
	biggest_tm.tm_mday = 31;
	biggest_tm.tm_hour = 23;
	biggest_tm.tm_min = 59;
	biggest_tm.tm_sec = 59;
	biggest = mktime(&biggest_tm);

	printf("biggest = %ld, %X, %s \n", biggest, biggest, ctime(&biggest));
	//printf("biggest = %ld, %LX, %s \n", biggest, biggest, asctime(gmtime(&biggest)));
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

