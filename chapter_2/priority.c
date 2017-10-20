#include <stdio.h>

int f()
{
	printf("f() called!\n");
	return 1;
}

int g()
{
	printf("g() called!\n");
	return 2;
}

int h()
{
	printf("h() called!\n");
	return 3;
}

int ff(int x, int y, int z)
{
	return x = y = z;
}

void main()
{
	int a, b = 1, c = 2;
	a = b = c;
	printf("a = %d.\n", a);
	
	int x = f() + g() * h();
	x = ff(f(), g(), h());
	
}