#include <stdio.h>
void f2();

int j;
int k = 10;
void f1()
{
	int i[100000];
	printf("The stack f1 is near %p.\n", &i);
	f2();
}

void f2()
{
	int i[100000];
	printf("The stack f2 is near %p.\n", &i);
}
void main()
{
	int i;
	printf("The stack top is near %p.\n", &i);
	f1();

	printf("The bss addr is near %p.\n", &j);
	printf("The data addr is near %p.\n", &k);
	printf("The text addr is near %p.\n", &f1);
}

