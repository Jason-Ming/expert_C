#include <stdio.h>
void banana_peel(char a, short b, float c);

void main()
{
    char a = 'x';
    short b = 0x1234;
    float c = 12.34;

    union
    {
        double d;
        float f;
    }u;

    u.d = 12.34;
    printf("put in a double, pull out of a float = %f \n", u.f);

    u.f = 12.34;
    printf("put in a float, pull out of a double = %f \n", u.d);

    banana_peel(a, b, c);
}

