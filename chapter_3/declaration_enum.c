#include <stdio.h>
enum sizes_tag
{
    small = 7,
    medium,
    large = 10,
    humungous
} sizes;

void f(enum sizes_tag s)
{
    printf("size = %d.\n", s);
}

void main()
{

    
    sizes = humungous;
    sizes = 12;
    f(sizes);
    printf("enums = %d, %d, %d, %d.\n", small, medium, large, humungous);
    
}
