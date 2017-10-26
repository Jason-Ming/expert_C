#include <stdio.h>

typedef int *ptr, (*fun)(), arr[5];

int x;
int f(){};

unsigned const long typedef int volatile *kumquat;

unsigned const long int volatile y;
int volatile z;

typedef int (*array_ptr)[100];
int array[100];

void main()
{
	ptr px = &x;
	fun fp = &f;
	arr a; 
	kumquat py = &y;
	array_ptr ap = &array;
}