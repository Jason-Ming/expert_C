#include <stdio.h>

union secondary_characteristics
{
    char has_fur;
    short num_of_legs_in_excess_of_4;
};

struct creature
{
    char has_backbone;
    union secondary_characteristics form;
};

union bits32_tag
{
    int whole;
    struct
    {
        char c0, c1, c2, c3;
    } byte;
} value;

void main()
{
    struct creature dog, butterfly;
    dog.has_backbone = 'y';
    dog.form.has_fur = 'y';
    
    butterfly.has_backbone = 'n';
    butterfly.form.num_of_legs_in_excess_of_4 = 6;
    
    union bits32_tag aInt;
    aInt.whole = 0x12345678;
    printf("int = %d.\n", aInt.whole);
    //little endian
    printf("byte = %x-%x-%x-%x.\n", aInt.byte.c0, aInt.byte.c1, aInt.byte.c2, aInt.byte.c3);
}