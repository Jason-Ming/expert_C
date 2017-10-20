#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_ELEMENTS(array) ((sizeof(array)/sizeof(array[0])))
char * f(char *p)
{
	/* static */
	char buff[8] = "abcdefg";
	return buff;//warning: function returns address of local variable [-Wreturn-local-addr]
}

char * f1()
{
	return "Only works for simple strings";
}

char my_global_array[8];
char * f2()
{
	for(int i = 0; i < TOTAL_ELEMENTS(my_global_array); i++)
	{
		my_global_array[i] = 'a' + i;
	}
	my_global_array[TOTAL_ELEMENTS(my_global_array)-1] = '\0';
	
	return my_global_array;
}

char * f3()
{
	static char buff[8] = "abcdefg";
	return buff;
}

char * f4()
{
	char *p = malloc(8);
	p[7] = '\0';
	return p;//memory leak!!!
}

void f5(char * result, int size)
{
	strncpy(result, "That'd be in the data segment, Bob",size);
}

void main()
{
	char* (*fp[])() = {f, f1, f2, f3, f4};
	
	for(int i = 0; i < TOTAL_ELEMENTS(fp); i++)
	{
		printf("String = %s.\n", (*fp[i])());
	}
	
	int size = 64;
	char *buffer = malloc(size);
	f5(buffer, size);
	printf("String = %s.\n", buffer);
	free(buffer);
}