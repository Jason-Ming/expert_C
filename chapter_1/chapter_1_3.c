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
    int y = x>>2;//������չ����λ
    printf("x = %d, y = %d\n", x, y);

    func(x + y, x++);//��������˳���Ǵ��ҵ���

    int z = 0x7FFFFFFF;
    printf("++z = %d\n", ++z);//�з�����������������С�ĸ���

    float f1 = 0.1;
    //float f2 = 10%f1; //error: invalid operands to binary % (have ��int�� and ��float��)

    char *p = "ABC";
    printf("%s\n", p);
    p = (char*)malloc(5);
    //printf("%s\n", p);//�δ���

    (void)printf("biggest int is %d\n", INT_MAX);//�������Ϊ2147483647
    return 0;
}

