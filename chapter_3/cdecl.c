#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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
struct struct_tag_token this;

#define POP stack[top--]
#define PUSH(s) stack[++top] = s
#define STRING_EQUAL(src, dest) (strcmp(src, dest) == 0)
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

struct struct_tag_classifier
{
    char string[MAXTOKENLEN];
    enum enum_tag_type type;
    char comment[MAXTOKENLEN];
};

struct struct_tag_classifier classifiers[] =
{
    {"const",    QUALIFIER, "read-only"},
    {"volatile", QUALIFIER, ""},
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
	char* s = this.string;

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

/* 读取下一个标记到this */
void get_token(void)
{
    char *p = this.string;

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

        this.type = classify_string();

        return;
    }

	/* 可能是*,[],() */
    if(*p == '*')
    {
		*(++p) = '\0';
		
        this.type = classify_string();
		return;
    }

	this.string[1] = '\0';
	this.type = *p;
	return;
}

#define GET_TOKEN {get_token(); /*printf("new token: %s, %d \n", this.string, this.type);*/}

/* 理解所有分析过程的代码段 */
void read_to_first_identifier()
{
	GET_TOKEN;
	
	while(this.type != IDENTIFIER)
	{
		PUSH(this);
		GET_TOKEN;
	}

	printf("%s is ", this.string);
	GET_TOKEN;
}

void deal_with_arrays(void)
{
	while(this.type == '[')
	{
		printf("array ");

		/* 数字或者] */
		GET_TOKEN;

		if(isdigit(this.string[0]))
		{
			printf("0..%d ", atoi(this.string) - 1);

			/* 读取] */
			GET_TOKEN;
		}

		GET_TOKEN;
		printf("of ");
	}
}

void deal_with_function_args(void)
{
	while(this.type != ')')
	{
		GET_TOKEN;
	}

	GET_TOKEN;
	printf("function returning ");
}

void deal_with_pointers(void)
{
	while(stack[top].type == POINTER)
	{
		printf("%s ", POP.string);
	}
}

void deal_with_declarator()
{
	/* 处理标识符之后可能存在的数组和函数 */
	switch(this.type)
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

	deal_with_pointers();

	/* 处理在读入标识符之前压入到堆栈中的符号 */
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
}

void main()
{
	/* 将标记压到堆栈中，直到遇见标识符 */
    read_to_first_identifier();
	deal_with_declarator();
	printf("\n");
	return;
    
}

