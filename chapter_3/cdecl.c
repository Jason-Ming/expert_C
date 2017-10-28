#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "utils_define.h"

#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum enum_tag_type
{
	IDENTIFIER,
	QUALIFIER,
	POINTER,
	TYPE
};

struct struct_tag_token
{
	char type;
	char string[MAXTOKENLEN];
};

int top = -1;
struct struct_tag_token stack[MAXTOKENS];
struct struct_tag_token current;

#define POP stack[top--]
#define PUSH(s) stack[++top] = s
#define STRING_EQUAL(src, dest) (strcmp(src, dest) == 0)
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

void print_stack()
{
    LOG("\n");
    
    for(int i = 0; i <= top; i++)
    {
        LOG("string = %16s, type = %d.\n", stack[i].string, stack[i].type);
    }
}

struct struct_tag_classifier
{
    char string[MAXTOKENLEN];
    enum enum_tag_type type;
    char comment[MAXTOKENLEN];
};

struct struct_tag_classifier classifiers[] =
{
    {"const",    QUALIFIER, "read-only"},
    {"volatile", QUALIFIER, "volatile"},
    {"void",     TYPE, ""},
    {"char",     TYPE, ""},
    {"signed",     TYPE, ""},
    {"unsigned",     TYPE, ""},
    {"short",     TYPE, ""},
    {"int",     TYPE, ""},
    {"long",     TYPE, ""},
    {"float",      TYPE, ""},
    {"double",     TYPE, ""},
    {"struct",      TYPE, ""},
    {"enum",      TYPE, ""},
    {"union",     TYPE, ""},
    {"*",         POINTER, "pointer to"}
};

/* 推断标识符的类型 */
enum enum_tag_type classify_string(void)
{
	char* s = current.string;

    for(int i = 0; i < ARRAY_SIZE(classifiers); i++)
    {
        if(STRING_EQUAL(s, classifiers[i].string))
        {
            if(strlen(classifiers[i].comment) != 0)
            {
                strcpy(s, classifiers[i].comment);
            }
            
            return classifiers[i].type;
        }    
    }
    
    return IDENTIFIER;
}

/* 读取下一个标记到current */
void get_token(void)
{
    char *p = current.string;

    /* 略过空白字符 */
    while((*p = getchar()) == ' ')
    {
    };

    /* 读入标识符以A~Z，0~9开头 */
    if(isalnum(*p))
    {
        while(isalnum(*++p = getchar()))
        {
        };

        ungetc(*p, stdin);
        *p = '\0';

        current.type = classify_string();

        return;
    }

	/* 可能是*,[],() */
    if(*p == '*')
    {
		*(++p) = '\0';
		
        current.type = classify_string();
		return;
    }

	current.string[1] = '\0';
	current.type = *p;
	return;
}

#define GET_TOKEN \
    {\
        get_token(); \
        LOG("new token: %s, %d \n", current.string, current.type);\
    }

/* 理解所有分析过程的代码段 */
void read_to_first_identifier()
{
    LOG("read_to_first_identifier.\n");
	GET_TOKEN;
	
	while(current.type != IDENTIFIER)
	{
		PUSH(current);
		GET_TOKEN;
	}

	printf("%s is ", current.string);
	GET_TOKEN;

    print_stack();
}

void deal_with_arrays(void)
{
    LOG("deal_with_arrays.\n");
	while(current.type == '[')
	{
		printf("array ");

		/* 数字或者] */
		GET_TOKEN;

		if(isdigit(current.string[0]))
		{
			printf("0..%d ", atoi(current.string) - 1);

			/* 读取] */
			GET_TOKEN;
		}

		GET_TOKEN;
		printf("of ");
	}
}

void deal_with_function_args(void)
{
    LOG("deal_with_function_args.\n");
    
    /* 忽略函数的参数 */
	while(current.type != ')')
	{
		GET_TOKEN;
	}

	GET_TOKEN;
	printf("function returning ");
}

void deal_with_pointers(void)
{
    LOG("deal_with_pointers.\n");
	while(stack[top].type == POINTER)
	{
		printf("%s ", POP.string);
	}
}

void deal_with_declarator()
{
    LOG("deal_with_declarator begin.\n");
    
	/* 处理标识符之后可能存在的数组和函数 */
	switch(current.type)
	{
		case '[' : 
		{
			deal_with_arrays();
			break;
		}

		case '(' :
		{
			deal_with_function_args();
			break;
		}
	}

    /* 处理在读入标识符之前压入到堆栈中的符号 */
	deal_with_pointers();

	while(top >= 0)
	{
		if(stack[top].type == '(')
		{
			POP;
			GET_TOKEN;
			deal_with_declarator();
		}
		else
		{
			printf("%s ", POP.string);
		}
	}

    LOG("deal_with_declarator end.\n");
}

void main()
{
	/* 将标记压到堆栈中，直到遇见标识符 */
    read_to_first_identifier();

	deal_with_declarator();

	printf("\n");

    LOG1("ss");

	return;
    
}

