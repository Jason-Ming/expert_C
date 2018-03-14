#include <stdio.h>
#include <time.h>
#include <limits.h>

/* this is the main function! */
int main()
{
	//ʵ�ʵ�64λ���У����ֵ��0x7FFFFFFF
    printf("INT_MAX = %X, %d\n", INT_MAX, INT_MAX);

	//��ӡ��ǰ��ʱ�䣬ʹ��time��ȡ��ʱ���Ǵ�ʱ����,ʹ��gmt��ȡ����ʱ��
    time_t current_time = time(&current_time);
    printf("current time = %s \n", ctime(&current_time));
	printf("current asctime = %s \n", asctime(gmtime(&current_time)));


	
    time_t biggest = INT_MAX;

	printf("biggest = %ld, %s \n", biggest, ctime(&biggest));
	printf("biggest = %ld, %s \n", biggest, asctime(gmtime(&biggest)));

	//ctime�ǽ�time_tת��Ϊ������ʾ��ʱ��,��Ϊ������ʾ��������ֵΪ32λ�з������������ֵ
	//��0x7FFFFFFF,��ô������������ֵΪ0x7FFFFFFF��12��31��23ʱ59��59��

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

