/* ���ں�����ʹ�ü������ο�gcc�ٷ��ĵ�: 
https://gcc.gnu.org/onlinedocs/cpp/Macros.html#Macros
*/

/*==========================================��ָ��================================================*/
/*
#if,#else,#elif,#endif,#ifdef,#ifndef���������������
���ԶԳ���ĸ���������ѡ��Ľ��б��롣����ǰ��������#if,#else,#elif,�������Ϊif��else����else if��
#endif���ʾ�����������ѡ��Ľ�����

#ifdef�жϺ���ı�ʶ���Ƿ񱻶��壬ͨ������ָԤ����ĺ꣬#ifndef����#ifdef��ȡ����

������������ν��������������һ������ͷ�ļ���������ʹ�䲻�ᱻ�ظ���������
�磺
#ifndef ANIMAL_H
#define ANIMAL_H
����
#endif

#ifndef������ͷ�ļ���������֮ǰ��#endif�Ƕ�������������֮��ģ���Ԥ��������#ifndef��#endif������
ͷ�ļ����ݰ�����������ͷ�ļ�����ͬ�ļ�����ʱ�Ͳ����б�������ˡ�ͨ����ϰ���������е�ͷ�ļ��ж��������������

�ؼ���#prama once����ȡ����ͬ�����ã���Ȼ�в�𣩡�
*/
#ifndef __CHAPTER_1_1_H__
#define __CHAPTER_1_1_H__



/*
#includeʹ�������#include��ָ���Դ�ļ��������ǰ��Դ�ļ������������ļ����뱻�����Ż����Ű�Χ������
ʹ��"#include��ָ�����ͷ�ļ�ʱ������ͷ�ļ������ַ�ʽ��һ����ʹ��˫����һ����ʹ�ü����š�
1)����ļ����ü���������������������ļ���һ�����̻���C++��׼��ͷ�ļ���Ԥ�����������������ڹ�����Ԥ�����Ŀ¼��
Ȼ������C++�������İ�װĿ¼������ͨ�����ù�������·��������������������ѡ�����޸ġ�
2)����ļ�����һ���������������������ļ����û��ṩ��ͷ�ļ���Ԥ���������ȴӵ�ǰ�ļ�Ŀ¼��ʼ����������Ҳ�����
�ʹӹ����ж����Ŀ¼�ͱ������İ�װĿ¼���ҡ����⣬Ҳ������ȷָ��ͷ�ļ���·�����������c�̵�ͷ�ļ�Header.h
#include ��c:/Header.h��
ע�⣺����#includeָ���C++��䣬������ͷ�ļ����ַ����У�����ʹ��˫б�������ÿһ��·����
*/
#include <stdio.h>
#include <stdlib.h>


//#undef
//#undef��������ȡ��ǰ�涨����ĺ�����
#define COMPILE_ERROR
#undef COMPILE_ERROR
#define COMPILE_OK
/*#
error����ǿ�ȱ�̳���ֹͣ���룬�����ڱ����ڼ�黷���Ƿ����Ҫ�����Լ�������������˳�ͻ����ʹ�ø�ʽ��:
#error token-string
�������ڱ����������������ؼ��֣��ͻ�ֹͣ���룬������һ��������Ϣ��������������token-string
*/
#ifdef COMPILE_ERROR
#error this is a compile error!
#endif

#ifndef COMPILE_OK
#error this is a compile error!
#endif

//����������ʱ����ʹ��#if defined��#if !defined������ʹ��#ifdef/#ifndef��
//��Ϊǰ�߸����㴦����֧�������ϸ����������ʽ�������
#if(defined(COMPILE_ERROR) || !defined(COMPILE_OK))
#error this is a compile error!
#endif
/*================================================================================================*/

/*==========================================�������==============================================*/
/*���������Ҫ��: #, ##, \ */
/*#���ַ�����һ������������ڲ�������ǰ�����"��*/
#define STRINGIZE(arg) #arg
/* 
arg���Դ�������Ҳ���Բ���������
1)��arg������������ʱ��Ԥ������ֻ�ᱣ���м��һ���ո񣬲���ǰ��Ŀո񽫱����ԣ���arg�а��������ַ�ʱ��
��Ҫʹ��ת���ַ�\��ʹ��%%���%
2)��arg����������ʱ��Ԥ�������ᱣ�����пո񣬲��һ��Զ��������ַ������ת���ַ�'\'�Ա�֤#arg�����������ַ�����
����%������Ҫ%%�����
*/
#define WARN_IF(EXP)    \
    do{ if (EXP)    \
            printf("Warning: " #EXP "\n"); }   \
    while(0)


//#@���ַ���һ������������ڲ�������ǰ�����'
//#define CHARIZE(x) #@x
//�������

//##��ƴ�Ӻ��������һ�����ţ�������������������һ���µķ��š�
#define SYMBOL_CATENATE(arg1, arg2) arg1 ## arg2  

/*������Ҫ��һ���˵����������ͺ���ָ����ɵĽṹ������飬����ϣ���ں������Ͳ˵���������֮����ֱ�۵ġ�
�����ϵĹ�ϵ����ô����Ĵ���ͷǳ�ʵ��*/
struct command
{
 char * name;
 void (*function) (void);
};

#define COMMAND_STRU_ELEMENT_INIT(NAME) { #NAME, NAME ## _command }
#define COMMAND_FUNC_DEF(NAME) void NAME ## _command(void){printf(#NAME"command execute!\n");}



/*ע�⣺���#��##�����Ĳ���Ҳ��һ���꣬��ô����꽫���ᱻ����չ�����������ȷʵ��Ҫ
#��##��ĺ����չ����Ҳ���Զ��帨�������һ�£�*/
#define foo 4
#define str(s) #s
#define xstr(s) str(s)


//\�����У�����ʼ�µ�һ�м���������塣
#define SWAP_INT(a, b) do\
{\
 int tmp = a; \
 a = b; \
 b = tmp; \
}while(0)
/*
ͨ��do-
while�����ĺ궨�����ǲ������԰�SWAP_INT����һ���ã����һ����ŵ㣺 
��1�����ں궨���п���ʹ�þֲ������� 
��2�����ں궨���п��԰��������䣬�����Ե���һ�����ʹ�ã�������е�if��֧��䣬���û��do-
while�Ѷ��������֯��һ������飬���������н���Ͳ���ȷ���������ܱ��롣
*/

/*================================================================================================*/


/*==========================================��κ�================================================*/
/*...��C���г�ΪVariadic Macro��Ҳ���Ǳ�κꡣ
��һ����������û�жԱ��������������Ĭ�ϵĺ�__VA_ARGS__���������
�ڶ������У�������ʽ���������Ϊargs����ô�����ں궨���оͿ�����args����ָ�����*/
#define Write_1(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define Write_2(fmt, args...) printf(fmt,##args)
/*================================================================================================*/



/*==========================================���ú�================================================*/
/*c/c++��׼��Ԥ�����˼����ֻ꣬Ҫ��������֧�ֱ�׼�ļ������ڴ�����ֱ��ʹ����Щ�꣺

__LINE__ // ��ǰ�����е��к�

__FILE__ // Դ���������·��

__DATE__ // ϵͳ����,���ڵõ����һ�α�������ں�ʱ��

__TIME__ // ϵͳʱ��,���ڵõ����һ�α�������ں�ʱ��

__TIMESTAMP__   // ϵͳʱ���,��__TIME__�ĸ�ʽ��ͬ��ͬ�ڵõ����ļ����һ�α��޸ĵ�ʱ�䡣

__FUNCTION__ // ��ǰ���������ڵĺ���������

__GNUC__��__GNUC_MINOR__��__GNUC_MINOR__��__GNUC_PATCHLEVEL__       ���ڵõ�GNU�汾��

__VERSION__  ���ڵõ��������İ汾

__COUNTER__ ��������������ڼ�¼��ǰ��������г��ֵ�__COUNTER__�Ĵ�������0��ʼ������
�����ڹ���һϵ�еı������ƣ��������Ƶȡ�

__INCLUDE_LEVEL__ ���ڱ�ʾ�ļ��������ļ�������0��ʼ����������Ϊ�ݹ����������������

__STDC__ // ��Ҫ������ϸ���ѭANSI C��׼ʱ�ñ�ʶ����ֵΪ1

__cplusplus // ����дC++����ʱ�ñ�ʶ��������

������һЩ�Ǳ�������ص�Ԥ����꣺

//VC��_MSC_VER// VC�������汾��

__i386__ 32λϵͳ
	
__x86_64__ 64λϵͳ

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



/*==========================================���ú�================================================*/
/*NULL*/
/*
NULL��һ���꣬���ڼ�����׼ͷ�ļ��ж��壬���ڱ�ʾʲôҲ��ָ��Ҳ���ǿ�ָ��((void *)0)
NULû�б�������C��C++������Ӧ�ñ�ʹ�ó������Լ�����������#define nul '\0

0��һ�����ͳ�����'\0'��һ���ַ���������
ע�⣺��ASCII�ַ����У�����0��Ӧ��ʮ����ֵ48����Ҫ������0��'\0'(NUL)��ֵ��ͬ������

\r��\n����һ���ַ����ֱ��ʾ�س��ͻ��У���ASC����ֵ�ֱ�Ϊ0x0D��0x0A��
windows���ı�һ�еĽ�β�����������ַ�\r\n��������unix��linux����ֻ��һ���ַ�\n��Mac��������ֻ���ַ�\r��
����������printf("\r");��printf("\n");�󲿷ֳ���ĳЩ����̨������⣩����û��̫������ġ�
�����ַ�Ϊʲôд��\����0��r��n�ȣ�����Ϊ��C�����б�ʾ�ַ����ַ���ʱ����\
��ת���ַ����򲻻����һ���ַ�ʶ��Ϊ��ͨ�ַ�������˵'\n'����ʾASC��0x0A��������ֵΪ0x6E����ĸn��
*/

//�����û�в����ĺ�
#define MAX_NUM 100

//��Ϊ��ֻ���滻չ�������Կ�����ɺ����޷���ɵĹ���
#define MALLOC(n, type) \
    ((type *) malloc((n)* sizeof(type)))

//��������Ԫ�صĸ���
#define  ARRAY_SIZE( a )  ( sizeof( (a) ) / sizeof( (a[0]) ) )

//�õ�ָ����ַ�ϵ�һ���ֽڻ���, intelƽ̨��С�ˣ��͵�ַ�洢���ݵĵ�λ
#define  VALUE_CHAR_OF_ADDR( x )  ( *( (char *) (x) ) )
#define  VALUE_SHORT_OF_ADDR( x )  ( *( (short *) (x) ) )

//�õ�һ��field�ڽṹ��(struct)�е�ƫ����
#define OFFSET_OF_MEMBER_IN_STRUCT(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)  

//�õ�һ���ṹ��(struct)����ʼ��ַ,ptrΪ��Ա�ĵ�ַ��typeΪstruct���ͣ�memberΪ��Ա������
#define CONTAINER_OF(ptr, type, member) ({\
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - offsetof(type,member) );})  

//�õ�һ���ṹ����field��ռ�õ��ֽ���
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

//�õ�һ�������ĵ�ַ��word��ȣ�
#define  CHAR_PTR_OF_VAR( var )  ( (char *) (void *) &(var) )
#define  SHORT_PTR_OF_VAR( var )  ( (short *) (void *) &(var) )

//�õ�һ���ֵĸ�λ�͵�λ�ֽ�
#define  SHORT_LO(var)  ((char) ((short)(var) & 0xFF))
#define  SHORT_HI(var)  ((char) (((short)(var) & 0xFF00) >> 8))


//�����ֵ����Сֵ
#define  MAX( x, y )  ( ((x) > (y)) ? (x) : (y) )
#define  MIN( x, y )  ( ((x) < (y)) ? (x) : (y) )

//����һ����X�����ӽ���n�ı���
#define RND_N( x , n )       ((((x) + (n-1)) / n ) * n )

//��һ����ĸת��Ϊ��д
#define  UPCASE( c ) ( ((c) >= ��a' && (c) <= ��z') ? ((c) - 0��20) : (c) )

//�ж��ַ��ǲ���10��ֵ������
#define  DECCHK( c ) ((c) >= ��0�� && (c) <= ��9��)

//�ж��ַ��ǲ���16��ֵ������
#define  HEXCHK( c ) ( ((c) >= ��0�� && (c) <= ��9��) ||((c) >= ��A' && (c) <= ��F') ||((c) >= ��a' && (c) <= ��f') )

//��ֹ�����һ������
#define  INC_SAT( val )  (val = ((val)+1 > (val)) ? (val)+1 : (val))


//����IO�ռ�ӳ���ڴ洢�ռ�Ľṹ�������������
#define REG_READ_CHAR(port)         (*((volatile  *) (port)))
#define REG_READ_SHORT(port)        (*((volatile short *) (port)))
#define REG_READ_INT(port)          (*((volatile int *)(port)))
#define REG_WRITE_CHAR(port, val)   (*((volatile char *) (port)) = ((char) (val)))
#define REG_WRITE_SHORT(port, val)  (*((volatile short *) (port)) = ((short) (val)))
#define REG_WRITE_INT(port, val)    (*((volatile int *) (port)) = ((int) (val)))




/*==========================================ע������==============================================*/
/*
1������ͨ�궨��
��1������һ���ô�д
��2��ʹ�ú����߳����ͨ���Ժ��׶��ԣ����ٲ�һ���ԣ������������ͱ����޸ġ�
��3��Ԥ�������ڱ���֮ǰ�Ĵ��������빤��������֮һ�����﷨��飬Ԥ�������﷨��顣
��4���궨��ĩβ���ӷֺţ�
��5���궨��д�ں����Ļ�������ߣ�������Ϊ���ĳ���ͨ�����ļ����ͷ��
��6��������#undef������ֹ�궨���������
��7���궨�����Ƕ��
��8���ַ���""����Զ��������
��9���궨�岻�����ڴ棬������������ڴ档
2�������κ궨��
��1��ʵ������Ǳ��ʽ���׳�����
��2�������Ͳ��������ż䲻���пո�
��3�����滻ֻ���滻���������㣬�������ʽ���,
��4�����������ڱ�����������ʱ���У����ҷ����ڴ档���滻�ڱ���ǰ���У��������ڴ�
��5�������ʵ��ϲ��������ͣ�Ҳû������ת����
��6������ֻ��һ������ֵ�����ú�������跨�õ����ֵ
��7����չ��ʹԴ����䳤���������ò���
��8����չ����ռ����ʱ�䣬ֻռ����ʱ�䣬��������ռ����ʱ�䣨�����ڴ桢�����ֳ���ֵ���ݡ�����ֵ��
��9����ֻ��չ����ע����Ҫ���ŵ����ȷ��Ԥ�ڵ�Ч��
*/

#ifdef __cplusplus
}
#endif

#endif

