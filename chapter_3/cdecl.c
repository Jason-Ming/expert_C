#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum enum_tag_type
{
	INDENTIFIER,
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
    
    return INDENTIFIER;
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

    if(*p == '*')
    {
        strcpy(this.string, "pointer to");
    }
}

void main()
{
    char p;
    while((p = getchar()) == ' ');
    printf("%c", p);
    
}

