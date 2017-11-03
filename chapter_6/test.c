#include <stdlib.h>

char pear[40];
static double peach;
int mango = 13;
static long melon = 2001;

void main()
{
    int a[1000000];// = {0};
    //int b[1000000] = {0};
    //int c[1000000] = {220};
    //static int x,y,z = 1;
    int i = 3, j, *ip;
    ip = malloc(sizeof(i));
    pear[5] = i;
    peach = 2.0 * mango;
}

