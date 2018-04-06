#include <stdio.h>

int array[] = {23, 34, 12, 17, 204, 99, 16};
int array0[] = {};
int array1[] = {23};
int array2[] = {23, 34};
#define TOTAL_ELEMENTS(array) (sizeof(array)/sizeof(array[0]))

void main()
{
	if( -1 < (unsigned char)1)
	{
		printf("-1 is less than (unsigned char)1: ANSI semantics.\n");
	}
	else
	{
		printf("-1 is NOT less than (unsigned char)1: K&R semantics.\n");
	}
	
	int d = -2, x = 10;
	
	unsigned int s = TOTAL_ELEMENTS(array);
	printf("s = %u.\n", s);
	
	if(d < s - 2)//d被转换为unsigned，故表达式的值为假
	{
		x = array[d+2];
	}
	
	printf("x = %d.\n", x);
}