#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void* malloc(size_t x){ return NULL;};

void func(int x, int y)
{
    printf("x = %d, y = %d\n", x, y);
}

int main()
{
    int x = -1024;
    int y = x>>2;//右移扩展符号位
    printf("x = %d, y = %d\n", x, y);

    func(x + y, x++);//参数计算顺序是从右到左

    int z = 0x7FFFFFFF;
    printf("++z = %d\n", ++z);//有符号整数溢出，变成最小的负数

    float f1 = 0.1;
    //float f2 = 10%f1; //error: invalid operands to binary % (have ‘int’ and ‘float’)

    char *p = "ABC";
    printf("%s\n", p);
    p = (char*)malloc(5);
    //printf("%s\n", p);//段错误

    (void)printf("biggest int is %d\n", INT_MAX);//最大整数为2147483647
    return 0;
}

