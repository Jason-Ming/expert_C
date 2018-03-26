#include <stdio.h>

struct T 
{
    char a;
    int b;
    char c;
};

struct E 
{
};

#define PRINT_SIZE(TYPE) printf("%16s %d\n", #TYPE, sizeof(TYPE));
void main()
{
	// Linux 平台 (基于 CentOS6.5)
	PRINT_SIZE(struct T);     //x86 12  x64 12
	PRINT_SIZE(struct E);     //x86 0   x64 0
	PRINT_SIZE(char);         //x86 1   x64 1   
	PRINT_SIZE(short int);    //x86 2   x64 2   
	PRINT_SIZE(int);          //x86 4   x64 4   
	PRINT_SIZE(long);         //x86 4   x64 8   
	PRINT_SIZE(long long);    //x86 8   x64 8   
	PRINT_SIZE(float);        //x86 4   x64 4   
	PRINT_SIZE(double);       //x86 8   x64 8   
	PRINT_SIZE(long double);  //x86 12  x64 16  
	PRINT_SIZE(void);         //x86 1   x64 1   
	PRINT_SIZE(void*);        //x86 4   x64 8   
	PRINT_SIZE(size_t);       //x86 4   x64 8   

	/*
	// Windows 平台 (基于 VS2013 Win10)
	PRINT_SIZE(struct T);     //x86 12  x64 12
	PRINT_SIZE(struct E);     //x86 1   x64 1
	PRINT_SIZE(short int);    //x86 2   x64 2
	PRINT_SIZE(int);          //x86 4   x64 4
	PRINT_SIZE(long);         //x86 4   x64 4
	PRINT_SIZE(long long);    //x86 8   x64 8
	PRINT_SIZE(float);        //x86 4   x64 4
	PRINT_SIZE(double);       //x86 8   x64 8
	PRINT_SIZE(long double);  //x86 8   x64 8
	//PRINT_SIZE(void);       //error C2070
	PRINT_SIZE(void*);        //x86 4   x64 8
	PRINT_SIZE(size_t);       //x86 4   x64 8s
	*/
}
