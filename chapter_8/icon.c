#include <stdio.h>

#define X )*2 + 1
#define _ )*2
#define s ((((((((((((((((0

static unsigned short stopwatch[] = 
{
    s _ _ _ _ _ X X X X X _ _ _ X X _,
    s _ _ _ X X X X X X X X X _ X X X,
    s _ _ X X X _ _ _ _ _ X X X _ X X,
    s _ X X _ _ _ _ _ _ _ _ _ X X _ _,
    s _ X X _ _ _ _ _ _ _ _ _ X X _ _,
    s X X _ _ _ _ _ _ _ _ _ _ _ X X _,
    s X X _ _ _ _ _ _ _ _ _ _ _ X X _,
    s X X _ X X X X X _ _ _ _ _ X X _,
    s X X _ _ _ _ _ X _ _ _ _ _ X X _,
    s X X _ _ _ _ _ X _ _ _ _ _ X X _,
    s _ X X _ _ _ _ X _ _ _ _ X X _ _,
    s _ X X _ _ _ _ X _ _ _ _ X X _ _,
    s _ _ X X X _ _ _ _ _ X X X _ _ _,
    s _ _ _ X X X X X X X X X _ _ _ _,
    s _ _ _ _ _ X X X X X _ _ _ _ _ _,
    s _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _,
};

#define ARRAY_SIZE(array) sizeof(array)/sizeof(array[0])

int main(void)
{
    for(int i = 0; i < ARRAY_SIZE(stopwatch); i++)
    {
        for(int j = 0; j < sizeof(unsigned short)*8; j++)
        {
            printf("%s ", (1 << (sizeof(unsigned short)*8 - j - 1) & stopwatch[i]) ? "X":"_");
        }
        printf("\n");
    }
}
