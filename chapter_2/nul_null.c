#include <stdio.h>
#define NUL '\0'
void main()
{
	char carray[4];
	char *p = NULL;
	for(int i = 0; i < 4; i++)
	{
		carray[i] = 'a' + i;
	}
	
	carray[3] = NUL;
	
	printf("carray = %s.\n", carray);
}