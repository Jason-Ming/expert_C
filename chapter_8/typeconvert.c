#include <stdio.h>

int main()
{
    /* �ڱ��ʽ�У�ÿ��char����ת��Ϊint��ע������λ�ڱ��ʽ�е�float����ת��Ϊdouble��
       ���ں�������Ҳ��һ�����ʽ�����Ե��������ݸ�����ʱҲ�ᷢ������ת���������˵��
       char��shortת��Ϊint����floatת��Ϊdouble */
    /* ������������ʵ����sizeof(int)�Ľ����4 */
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

