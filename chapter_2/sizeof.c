#include <stdio.h>

#define N 8

void main()
{
	int p;
	short *q;
	p = N * sizeof *q;
	
	printf("p = %d.\n", p);
	
	int apple =  sizeof(int) *q;
	//invalid operands to binary * (have ‘unsigned int’ and ‘short int *’)
	apple =  sizeof(int) *(int)q;
	apple =  sizeof((int) *q);
}