#include <stdio.h>

//结构定义中加标签
struct data_tag 
{
	short dd, mm, yy;
} my_birthday, xmas;

struct data_tag easter, groundhog_day;


//位域
struct pid_tag
{
	unsigned int inactive : 1;
	unsigned int          : 1; /* 一个位的填充 */
	unsigned int refcount : 6;
	unsigned int          : 0; /* 填充到下一个字边界 */
	short pid;
	struct pid_tag *link;
}

//类型定义和变量声明分开
struct veg 
{
	int weight, price_per_1b;
}

struct veg onion, radish, turnip;

//数组定义在结构体内
struct s_tag
{
	int a[100];
};

struct s_tag orange, lime, lemon;

//结构体作为参数是拷贝传值
struct s_tag twofold(struct s_tag s)
{
	int j;
	for(j = 0; j < 100; j++)
	{
		s.a[j] *= 2;
	}
	return s;
}

struct node_tag
{
	int datum;
	struct node_tag *next;
};

struct node_tag a, b;

void main()
{
	int i;
	for(i = 0; i < 100; i++)
	{
		lime.a[i] = 1;
	}
	
	lemon = twofold(lime);
	orange = lemon; //给整个结构赋值
	
	a.next = &b;
	a.next->next = NULL;
	
}