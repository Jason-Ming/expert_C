#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum type_tag
{
	INDENTIFIER,
	QUALIFIER,
	TYPE
};

struct token
{
	char type;
	char string[MAXTOKENLEN];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token this;

#define POP stack[top--]
#define PUSH(s) stack[++top] = s

/* �ƶϱ�ʶ�������� */
enum type_tag classify_string(void)
{
	
}
