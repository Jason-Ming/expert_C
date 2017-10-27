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

/* �ƶϱ�ʶ�������� */
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

/* ��ȡ��һ����ǵ�this */
void get_token(void)
{
    char *p = this.string;

    /* �Թ��հ��ַ� */
    while((*p = getchar()) == ' ')
    {
    };

    /* �����ʶ����A~Z��0~9��ͷ */
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

	/* ������*,[],() */
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

/* ������з������̵Ĵ���� */
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

		/* ���ֻ���] */
		GET_TOKEN;

		if(isdigit(this.string[0]))
		{
			printf("0..%d ", atoi(this.string) - 1);

			/* ��ȡ] */
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
	/* �����ʶ��֮����ܴ��ڵ�����ͺ��� */
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

	/* �����ڶ����ʶ��֮ǰѹ�뵽��ջ�еķ��� */
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
	/* �����ѹ����ջ�У�ֱ��������ʶ�� */
    read_to_first_identifier();
	deal_with_declarator();
	printf("\n");
	return;
    
}

