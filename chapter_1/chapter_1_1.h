/* 关于宏的相关使用及事项，请参考gcc官方文档: 
https://gcc.gnu.org/onlinedocs/cpp/Macros.html#Macros
*/

/*==========================================宏指令================================================*/
/*
#if,#else,#elif,#endif,#ifdef,#ifndef属于条件编译命令，
可以对程序的各个部分有选择的进行编译。对于前面三个宏#if,#else,#elif,可以理解为if，else，和else if，
#endif则表示这个条件编译选择的结束。

#ifdef判断后面的标识符是否被定义，通常都是指预定义的宏，#ifndef就是#ifdef的取反。

包含警卫：所谓包含警卫就是用一组宏命令将头文件包起来，使其不会被重复包含。例
如：
#ifndef ANIMAL_H
#define ANIMAL_H
……
#endif

#ifndef定义在头文件所有内容之前，#endif是定义在所有内容之后的，用预编译命令#ifndef和#endif将整个
头文件内容包起来。这样头文件被不同文件包含时就不会有编译错误了。通常的习惯是在所有的头文件中都加入包含警卫。

关键字#prama once可以取到相同的作用（仍然有差别）。
*/
#ifndef __CHAPTER_1_1_H__
#define __CHAPTER_1_1_H__



/*
#include使编译程序将#include所指向的源文件导入进当前的源文件，被包含的文件必须被尖括号或引号包围起来。
使用"#include”指令包含头文件时，其后的头文件有两种方式，一种是使用双引号一种是使用尖括号。
1)如果文件名用尖括号括起来，表面这个文件是一个工程或者C++标准库头文件。预编译器会首先搜索在工程中预定义的目录，
然后搜索C++编译器的安装目录。可以通过设置工程搜索路径环境变量或者命令行选项来修改。
2)如果文件名用一对引号括起来，则表面该文件是用户提供的头文件。预编译器首先从当前文件目录开始搜索，如果找不到，
就从工程中定义的目录和编译器的安装目录查找。另外，也可以明确指定头文件的路径。例如包含c盘的头文件Header.h
#include “c:/Header.h”
注意：由于#include指令不是C++语句，所以在头文件的字符串中，不必使用双斜杠来间隔每一级路径。
*/
#include <stdio.h>
#include <stdlib.h>


//#undef
//#undef命令用来取消前面定义过的宏名。
#define COMPILE_ERROR
#undef COMPILE_ERROR
#define COMPILE_OK
/*#
error可以强迫编程程序停止编译，用来在编译期检查环境是否符合要求或者约束的条件发生了冲突。其使用格式是:
#error token-string
当程序在编译过程中遇到这个关键字，就会停止编译，产生了一个错误信息，并且输出后面的token-string
*/
#ifdef COMPILE_ERROR
#error this is a compile error!
#endif

#ifndef COMPILE_OK
#error this is a compile error!
#endif

//在条件编译时建议使用#if defined和#if !defined来代替使用#ifdef/#ifndef，
//因为前者更方便处理多分支的情况与较复杂条件表达式的情况。
#if(defined(COMPILE_ERROR) || !defined(COMPILE_OK))
#error this is a compile error!
#endif
/*================================================================================================*/

/*==========================================宏操作符==============================================*/
/*宏操作符主要有: #, ##, \ */
/*#：字符串化一个宏参数，即在参数名字前后加上"。*/
#define STRINGIZE(arg) #arg
/* 
arg可以带“”，也可以不带“”，
1)当arg参数不带“”时，预处理器只会保留中间的一个空格，并且前后的空格将被忽略，当arg中包含特殊字符时，
需要使用转义字符\，使用%%输出%
2)当arg参数带“”时，预处理器会保留所有空格，并且会自动将特殊字符添加上转义字符'\'以保证#arg返回完整的字符串，
但是%还是需要%%来输出
*/
#define WARN_IF(EXP)    \
    do{ if (EXP)    \
            printf("Warning: " #EXP "\n"); }   \
    while(0)


//#@：字符化一个宏参数，即在参数名字前后加上'
//#define CHARIZE(x) #@x
//编译错误

//##：拼接宏参数和另一个符号，即连接两个符号生成一个新的符号。
#define SYMBOL_CATENATE(arg1, arg2) arg1 ## arg2  

/*比如你要做一个菜单项命令名和函数指针组成的结构体的数组，并且希望在函数名和菜单项命令名之间有直观的、
名字上的关系。那么下面的代码就非常实用*/
struct command
{
 char * name;
 void (*function) (void);
};

#define COMMAND_STRU_ELEMENT_INIT(NAME) { #NAME, NAME ## _command }
#define COMMAND_FUNC_DEF(NAME) void NAME ## _command(void){printf(#NAME"command execute!\n");}



/*注意：如果#、##操作的参数也是一个宏，那么这个宏将不会被继续展开，但是如果确实需要
#、##后的宏继续展开，也可以定义辅助宏过度一下：*/
#define foo 4
#define str(s) #s
#define xstr(s) str(s)


//\：换行，即开始新的一行继续定义宏体。
#define SWAP_INT(a, b) do\
{\
 int tmp = a; \
 a = b; \
 b = tmp; \
}while(0)
/*
通过do-
while代码块的宏定义我们不仅可以把SWAP_INT像函数一样用，而且还有优点： 
（1）、在宏定义中可以使用局部变量； 
（2）、在宏定义中可以包含多个语句，但可以当作一条语句使用，如代码中的if分支语句，如果没有do-
while把多条语句组织成一个代码块，则程序的运行结果就不正确，甚至不能编译。
*/

/*================================================================================================*/


/*==========================================变参宏================================================*/
/*...在C宏中称为Variadic Macro，也就是变参宏。
第一个宏中由于没有对变参起名，我们用默认的宏__VA_ARGS__来替代它。
第二个宏中，我们显式地命名变参为args，那么我们在宏定义中就可以用args来代指变参了*/
#define Write_1(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define Write_2(fmt, args...) printf(fmt,##args)
/*================================================================================================*/



/*==========================================内置宏================================================*/
/*c/c++标准中预定义了几个宏，只要编译器是支持标准的即可以在代码中直接使用这些宏：

__LINE__ // 当前代码行的行号

__FILE__ // 源程序的完整路径

__DATE__ // 系统日期,用于得到最后一次编译的日期和时间

__TIME__ // 系统时间,用于得到最后一次编译的日期和时间

__TIMESTAMP__   // 系统时间戳,和__TIME__的格式相同。同于得到本文件最后一次被修改的时间。

__FUNCTION__ // 当前代码行所在的函数的名字

__GNUC__、__GNUC_MINOR__、__GNUC_MINOR__、__GNUC_PATCHLEVEL__       用于得到GNU版本：

__VERSION__  用于得到编译器的版本

__COUNTER__ 自身计数器，用于记录以前编译过程中出现的__COUNTER__的次数，从0开始计数。
常用于构造一系列的变量名称，函数名称等。

__INCLUDE_LEVEL__ 用于表示文件被包含的计数，从0开始递增，常作为递归包含的限制条件。

__STDC__ // 当要求程序严格遵循ANSI C标准时该标识被赋值为1

__cplusplus // 当编写C++程序时该标识符被定义

另外有一些是编译器相关的预定义宏：

//VC：_MSC_VER// VC编译器版本号

__i386__ 32位系统
	
__x86_64__ 64位系统

*/
#define PRINT_PREDEFINE_MACROS\
    printf("file: %s, basefile: %s, line: %u, date: %s, time: %s, timestamp: %s, function: %s\n",\
    __FILE__, __BASE_FILE__, __LINE__, __DATE__, __TIME__, __TIMESTAMP__, __FUNCTION__);

#define PRINT_GCC_VER\
    printf("compiler version: %s, gnuc: %d, gnuc_minor: %d, gnuc_pathlevel: %d\n", \
    __VERSION__, __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);

#define VAR2(x,y) x##y  
#define VAR1(x,y) VAR2(x,y)    
#define VAR(x) VAR1(x,__COUNTER__)  
  
int VAR(var);  
int VAR(var); 

const char include_file_name[] = __BASE_FILE__;
#define REP_LIMIT 10
#define REP(BLAH) printf("%s, %d \n", include_file_name, BLAH); 

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================================================*/



/*==========================================常用宏================================================*/
/*NULL*/
/*
NULL是一个宏，它在几个标准头文件中定义，用于表示什么也不指向，也就是空指针((void *)0)
NUL没有被定义于C和C++，它不应该被使用除非你自己定义它，像：#define nul '\0

0是一个整型常量，'\0'是一个字符常量，。
注意：在ASCII字符集中，数字0对应于十进制值48，不要把数字0和'\0'(NUL)的值混同起来。

\r和\n都是一个字符，分别表示回车和换行，在ASC码里值分别为0x0D、0x0A，
windows中文本一行的结尾都是有两个字符\r\n，但是在unix、linux里面只有一个字符\n，Mac里面则是只有字符\r，
但是你是用printf("\r");或printf("\n");大部分程序（某些控制台程序除外）都是没有太大区别的。
至于字符为什么写成\加上0、r和n等，是因为在C语言中表示字符或字符串时遇到\
（转义字符）则不会把下一个字符识别为普通字符，比如说'\n'，表示ASC码0x0A，而不是值为0x6E的字母n。
*/

//宏对象，没有参数的宏
#define MAX_NUM 100

//因为宏只是替换展开，所以可以完成函数无法完成的工作
#define MALLOC(n, type) \
    ((type *) malloc((n)* sizeof(type)))

//返回数组元素的个数
#define  ARRAY_SIZE( a )  ( sizeof( (a) ) / sizeof( (a[0]) ) )

//得到指定地址上的一个字节或字, intel平台是小端，低地址存储数据的低位
#define  VALUE_CHAR_OF_ADDR( x )  ( *( (char *) (x) ) )
#define  VALUE_SHORT_OF_ADDR( x )  ( *( (short *) (x) ) )

//得到一个field在结构体(struct)中的偏移量
#define OFFSET_OF_MEMBER_IN_STRUCT(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)  

//得到一个结构体(struct)的起始地址,ptr为成员的地址，type为struct类型，member为成员的名字
#define CONTAINER_OF(ptr, type, member) ({\
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - offsetof(type,member) );})  

//得到一个结构体中field所占用的字节数
#define SIZE_OF_MEMBER_IN_STRUCT( type, field ) sizeof( ((type *) 0)-> field )

typedef struct TAG_STRU_T
{
    char c;
    short s;
    int i;
    long int li;
    long long int lli;
    float f;
    double d;
}STRU_T;

#ifdef __i386__
#define PRINT_STRU_MEMBER_INFO(type, field) printf("%s.%s: offset = %u, size = %u\n", \
    #type, #field, OFFSET_OF_MEMBER_IN_STRUCT(type, field), SIZE_OF_MEMBER_IN_STRUCT(type, field));
#elif  __x86_64__
#define PRINT_STRU_MEMBER_INFO(type, field) printf("%s.%s: offset = %lu, size = %lu\n", \
    #type, #field, OFFSET_OF_MEMBER_IN_STRUCT(type, field), SIZE_OF_MEMBER_IN_STRUCT(type, field));
#endif

#define PRINT_STRU_MEMBER\
    do{\
        PRINT_STRU_MEMBER_INFO(STRU_T, c);\
        PRINT_STRU_MEMBER_INFO(STRU_T, s);\
        PRINT_STRU_MEMBER_INFO(STRU_T, i);\
        PRINT_STRU_MEMBER_INFO(STRU_T, li);\
        PRINT_STRU_MEMBER_INFO(STRU_T, lli);\
        PRINT_STRU_MEMBER_INFO(STRU_T, f);\
        PRINT_STRU_MEMBER_INFO(STRU_T, d);\
    }while(0);

//得到一个变量的地址（word宽度）
#define  CHAR_PTR_OF_VAR( var )  ( (char *) (void *) &(var) )
#define  SHORT_PTR_OF_VAR( var )  ( (short *) (void *) &(var) )

//得到一个字的高位和低位字节
#define  SHORT_LO(var)  ((char) ((short)(var) & 0xFF))
#define  SHORT_HI(var)  ((char) (((short)(var) & 0xFF00) >> 8))


//求最大值和最小值
#define  MAX( x, y )  ( ((x) > (y)) ? (x) : (y) )
#define  MIN( x, y )  ( ((x) < (y)) ? (x) : (y) )

//返回一个比X大的最接近的n的倍数
#define RND_N( x , n )       ((((x) + (n-1)) / n ) * n )

//将一个字母转换为大写
#define  UPCASE( c ) ( ((c) >= ’a' && (c) <= ’z') ? ((c) - 0×20) : (c) )

//判断字符是不是10进值的数字
#define  DECCHK( c ) ((c) >= ’0′ && (c) <= ’9′)

//判断字符是不是16进值的数字
#define  HEXCHK( c ) ( ((c) >= ’0′ && (c) <= ’9′) ||((c) >= ’A' && (c) <= ’F') ||((c) >= ’a' && (c) <= ’f') )

//防止溢出的一个方法
#define  INC_SAT( val )  (val = ((val)+1 > (val)) ? (val)+1 : (val))


//对于IO空间映射在存储空间的结构，输入输出处理
#define REG_READ_CHAR(port)         (*((volatile  *) (port)))
#define REG_READ_SHORT(port)        (*((volatile short *) (port)))
#define REG_READ_INT(port)          (*((volatile int *)(port)))
#define REG_WRITE_CHAR(port, val)   (*((volatile char *) (port)) = ((char) (val)))
#define REG_WRITE_SHORT(port, val)  (*((volatile short *) (port)) = ((short) (val)))
#define REG_WRITE_INT(port, val)    (*((volatile int *) (port)) = ((int) (val)))




/*==========================================注意事项==============================================*/
/*
1）、普通宏定义
（1）宏名一般用大写
（2）使用宏可提高程序的通用性和易读性，减少不一致性，减少输入错误和便于修改。
（3）预处理是在编译之前的处理，而编译工作的任务之一就是语法检查，预处理不做语法检查。
（4）宏定义末尾不加分号；
（5）宏定义写在函数的花括号外边，作用域为其后的程序，通常在文件的最开头。
（6）可以用#undef命令终止宏定义的作用域
（7）宏定义可以嵌套
（8）字符串""中永远不包含宏
（9）宏定义不分配内存，变量定义分配内存。
2）、带参宏定义
（1）实参如果是表达式容易出问题
（2）宏名和参数的括号间不能有空格
（3）宏替换只作替换，不做计算，不做表达式求解,
（4）函数调用在编译后程序运行时进行，并且分配内存。宏替换在编译前进行，不分配内存
（5）宏的哑实结合不存在类型，也没有类型转换。
（6）函数只有一个返回值，利用宏则可以设法得到多个值
（7）宏展开使源程序变长，函数调用不会
（8）宏展开不占运行时间，只占编译时间，函数调用占运行时间（分配内存、保留现场、值传递、返回值）
（9）宏只做展开，注意需要括号的配合确保预期的效果
*/

#ifdef __cplusplus
}
#endif

#endif

