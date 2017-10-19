void foo(const char **p)
{
	
}

main(int argc, char **argv)
{
	//foo(argv);
	int i=10,j = 10;
	int const x = 10;
	const int *p = &x;
	p = &j;
	//*p = 11;
	int const const *const plimit = &x;
	//plimit = &i;
	
	//*plimit = 11;
	char **cpp;
	const char ** ccpp;
	ccpp = cpp;

}