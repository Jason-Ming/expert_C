#include <stddef.h>
#include "chapter_1_1.h"


COMMAND_FUNC_DEF(quit);
COMMAND_FUNC_DEF(help);

void main()
{
    int array[MAX_NUM] = {0};

    int *p = MALLOC(MAX_NUM, int);
    WARN_IF(p == NULL);

    printf(STRINGIZE("  A' B   \ C #$^@^$\%% ")" aaa\n" STRINGIZE(""""""));

    printf(STRINGIZE(  A B   \\ C #$^@^$\%%   )" aaa\n" );

    struct command commands[] = {
        COMMAND_STRU_ELEMENT_INIT(quit),
        COMMAND_STRU_ELEMENT_INIT(help),
    };

    if(p != NULL)
    {
        int x = 0, y = 1;
        Write_1("no param!\n");
        Write_2("no param!\n");
        Write_1("x is %d and y is %d\n", x, y);
        SWAP_INT(x, y);
        Write_2("x is %d and y is %d\n", x, y);
    }
    else
    {
        //for...
    }

    printf(str (foo)"\n");
    printf(xstr(foo)"\n");

    //printf("%c\n",CHARIZE(arg));

    PRINT_PREDEFINE_MACROS;
    PRINT_GCC_VER;

    int var0 = 0, var1 = 1;
    printf("%d\n",var0);  
    printf("%d\n",var1);  
    
    #include "chapter_1_1_nesting.h"

    printf("size of commands[] : %lu\n", (long unsigned int)ARRAY_SIZE(commands) );

    long long *pll, ll = 0x0123456789abcdef;
    pll = &ll;
    char ch = VALUE_CHAR_OF_ADDR(pll);
    short sh = VALUE_SHORT_OF_ADDR(pll);
    printf("VALUE_CHAR_OF_ADDR(%llx): %hhd, %hhx\n", ll, ch, ch);//VALUE_CHAR_OF_ADDR(pll));
    printf("VALUE_SHORT_OF_ADDR(%llx): %hd, %hx\n", ll, sh, sh);//VALUE_SHORT_OF_ADDR(pll));
    
    printf("MAX(%d, %d) = %d\n", var1,var0,MAX(var1,var0));
    printf("MIN(%d, %d) = %d\n", var0,var1,MIN(var1,var0));
    
    STRU_T t;
    PRINT_STRU_MEMBER;
    printf("address of struct: %p, %p\n", &t, CONTAINER_OF(&(t.li), STRU_T, li));

    printf("CHAR_PTR_OF_VAR: %p, char: %d, SHORT_PTR_OF_VAR: %p, short: %d\n", 
        CHAR_PTR_OF_VAR(ll), *CHAR_PTR_OF_VAR(ll), SHORT_PTR_OF_VAR(ll), *SHORT_PTR_OF_VAR(ll));

    printf("SHORT_LO(%d): %d, %hhx, SHORT_HI(%d): %d, %hhx\n", sh, SHORT_LO(sh), SHORT_LO(sh),
        sh, SHORT_HI(sh), SHORT_HI(sh));

    printf("RND_N(%d, %d): %d\n", 5, 3, RND_N(5, 6));
    
}