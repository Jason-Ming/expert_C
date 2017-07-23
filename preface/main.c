#include <stdio.h>
#include <time.h>

/*this is the main function!*/
int main()
{
    
    
    time_t current_time = time(&current_time);
    printf("current time = %s \n", ctime(&current_time));
    
    time_t biggest = 0xFFFFFFFF;
    printf("biggest = %s \n", ctime(&biggest));
    printf("biggest = %s \n", asctime(gmtime(&biggest)));
    
    double diff  = difftime(biggest, current_time);
    double minutes = diff/60;
    double hours = minutes/60;
    double days = hours/24;
    double weeks = days/7;
    double months = days/30;
    double years = days/365;
    
    printf("diff time(%f)seconds = %f years, %f months, %f weeks, %f days, %f hours, %f minutes \n", 
        diff, years, months, weeks, days, hours, minutes);
    
    return 0;
}
