#include <stdio.h>

int main()
{
    /* 在表达式中，每个char都被转换为int，注意所有位于表达式中的float都被转换为double，
       由于函数参数也是一个表达式，所以当参数传递给函数时也会发生类型转换。具体的说，
       char和short转换为int，而float转换为double */
    /* 所以下面的输出实际是sizeof(int)的结果，4 */
    printf("%d, %d.\n", sizeof(char), sizeof('a'));
    char a = 'a';
    short x = 56;
    float i = 0.4f;
    double j = 0.004;

    printf("%d, %d, %d.\n", sizeof(char), sizeof(a), sizeof(a + 'a'));
    printf("%d, %d, %d.\n", sizeof(short), sizeof(x), sizeof(x + 0));
    printf("%d, %d, %d.\n", sizeof(float), sizeof(i), sizeof(i + 0.1));
    printf("%d, %d, %d.\n", sizeof(double), sizeof(j), sizeof(j + 0.1));
    
    return 0;
}

