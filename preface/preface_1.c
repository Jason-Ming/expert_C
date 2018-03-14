#include <stdio.h>
#include <time.h>
#include <limits.h>

/* this is the main function! */
int main()
{
	//实际的64位机中，这个值是0x7FFFFFFF
    printf("INT_MAX = %X, %d\n", INT_MAX, INT_MAX);

	//打印当前的时间，使用time获取的时间是带时区的,使用gmt获取世界时间
    time_t current_time = time(&current_time);
    printf("current time = %s \n", ctime(&current_time));
	printf("current asctime = %s \n", asctime(gmtime(&current_time)));


	
    time_t biggest = INT_MAX;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));

	//ctime是将time_t转换为可以显示的时间,因为它能显示的年的最大值为32位有符号整数的最大值
	//即0x7FFFFFFF,那么其能输入的最大值为0x7FFFFFFF年12月31日23时59分59秒

	struct tm biggest_tm;
	biggest_tm.tm_year = 0x7FFFFFFF - 1900;
	biggest_tm.tm_mon = 11;
	biggest_tm.tm_mday = 31;
	biggest_tm.tm_hour = 23;
	biggest_tm.tm_min = 59;
	biggest_tm.tm_sec = 59;
	biggest = mktime(&biggest_tm);

	
	printf("biggest = %ld, %LX, %s \n", biggest, biggest, ctime(&biggest));
	printf("biggest = %ld, %LX, %s \n", biggest, biggest, asctime(gmtime(&biggest)));

    
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

