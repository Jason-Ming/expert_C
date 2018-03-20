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

	//strftime() 函数将时间格式化
	//我们可以使用strftime（）函数将时间格式化为我们想要的格式。它的原型如下：
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

	//ctime是将time_t转换为可以显示的时间字符串,是带时区的本地时间
	//%lx输出长整型long的十六进制表示，%llx和%Lx表示longlong的十六进制表示
	printf("	>>>>	      %s = %ld, %lX, %s \n", s, t, t, ctime(&t));
	
	//asctime是将struct tm转换为时间字符串，将结构中的年月日小时分秒原样显示
	printf("	>>>>	  gmt %s = %ld, %lX, %s \n", s, t, t, asctime(gmtime(&t)));
	print_tm(gmtime(&t));
		
	printf("	>>>>	local %s = %ld, %lX, %s \n", s, t, t, asctime(localtime(&t)));
	print_tm(localtime(&t));

	printf("=====END=======----------------------------------------------------------------\n");	
}

int main()
{
	//实际的64和32位机中，这个值都是0x7FFFFFFF
    printf("INT_MAX = %X, %d\n", INT_MAX, INT_MAX);
	
	//UTC时间有三种表示方法:
	//(1)
	//time_t 一般在time.h头文件中定义为long, 在32位机中是32位, 在64位机中是64位
	//time_t 表示基于标准时间1970年1月1日0时0分0秒到现在的秒数，在任何时区内，这个值都是一定的。
	//time_t time(time_t *t); 使用time获取当前时间戳time_t

	time_t current_time = time(&current_time);
	print_time("current time", current_time);

	//(2)
	//struct tm是存储的时间的结构
	//struct tm
	//{
	//    int tm_sec;  /*秒，正常范围0-59， 但允许至61*/
	//    int tm_min;  /*分钟，0-59*/
	//    int tm_hour; /*小时， 0-23*/
	//    int tm_mday; /*日，即一个月中的第几天，1-31*/
	//    int tm_mon;  /*月， 从一月算起，0-11*/  1+p->tm_mon;
	//    int tm_year;  /*年， 从1900至今已经多少年*/  1900＋ p->tm_year;
	//    int tm_wday; /*星期，一周中的第几天， 从星期日算起，0-6*/
	//    int tm_yday; /*从今年1月1日到目前的天数，范围0-365*/
	//    int tm_isdst; /*日光节约时间的旗标*/
	//};
	//struct tm* gmtime(const time_t *timep);将time_t表示的时间转换为UTC时间，
	//是一个struct tm结构指针,即0时区
	//struct tm* localtime(const time_t *timep);
	//和gmtime类似，但是它是经过时区转换的时间。


	//(3)
	//struct timeval，它精确到微妙。
	//struct timeval
	//{
    //	long tv_sec; /*秒*/
    //	long tv_usec; /*微秒*/
	//};
	//使用int gettimeofday(struct timeval *tv, struct timezone *tz);
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	printf("current time: %ld seconds, %ld useconds.\n", tv.tv_sec, tv.tv_usec);

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


	//但是因为ctime/asctime它能显示的年的最大值为32位有符号整数的最大值即0x7FFFFFFF,
	//那么其能输入的最大值为0x7FFFFFFF年12月31日23时59分59秒
	
	//以下讨论的gmt的各种值和假设都基于东八区与标准时间，东区时是下面的最大值，
	//西区时需要减去时区，因为UTC时间要大于本地时间

	struct tm biggest_tm;
	biggest_tm.tm_year = 0x7FFFFFFF - 1900;//int 类型，记录1900年之后的年数
	biggest_tm.tm_mon = 11;
	biggest_tm.tm_mday = 31;
	biggest_tm.tm_hour = 23;
	biggest_tm.tm_min = 59;
	biggest_tm.tm_sec = 59;

	//mktime用来将参数所指的tm结构数据转换成从公元1970年1月1日0时0分0 秒算起至今的UTC时间所经过的秒数。
	//既然得到的是秒数，那么就是说无论在世界任何的地方，得到的结果都是一样的，也就是说该函数处理的是本地时间
	time_t biggest = mktime(&biggest_tm);

	print_time("biggest", biggest);
	

	//最小值为0x80000000年1月1日0时0分0秒，但是小于1900年的时候，
	//所以虽然能显示格式化的时间，但gmtime(&t)的值会出现问题，与t相差的不是整数倍的时区
	//如下时间为最小的t可以正常计算时区的时间
	struct tm smallest_tm;
	smallest_tm.tm_year = 00;
	smallest_tm.tm_mon = 11;
	smallest_tm.tm_mday = 31;
	smallest_tm.tm_hour = 23;
	smallest_tm.tm_min = 54;
	smallest_tm.tm_sec = 17;
	time_t smallest = mktime(&smallest_tm);

	print_time("smallest", smallest);

	//若不考虑gmtime(&t)的问题，以东八区为例相差8小时5分43秒，那么最小可格式化显示的值为
	//其他时区的时间值不确定，没有试验
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

