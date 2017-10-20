#incl\
ude <stdio.h>

void main()
{
	char a[] = "Hi! How are you? I am quite a \ 
	long string, foled onto 2 lines!";
	
	printf("string = %s.\n", a);
	
	int z = 1, y = 2, x = 3;
	z = y+++x;//z = y++ + x
	z = y+++++x;//error: lvalue required as increment operand
	printf("z = %d, y = %d, x = %d.\n", z, y, x);
}