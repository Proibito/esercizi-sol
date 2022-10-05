#include <stdio.h>

/* Convenient macro to print conditions and their value */
#define TESTING_CONDITIONS(cond)	printf("%s is \t", #cond);	\
											if(cond)			\
											printf("TRUE\n");	\
											else				\
											printf("FALSE\n");

int main()
{
	TESTING_CONDITIONS(1);
	TESTING_CONDITIONS(0);
	TESTING_CONDITIONS(-1);
	TESTING_CONDITIONS(11 > 10);
	TESTING_CONDITIONS(011 > 10);
	TESTING_CONDITIONS(-1 < 0);
	TESTING_CONDITIONS(-1U < 0);
	TESTING_CONDITIONS(-1 == -1);
	TESTING_CONDITIONS(-1U == -1L);
	TESTING_CONDITIONS(1e10+1 == 1e10);
	TESTING_CONDITIONS(1e15+1 == 1e15);
	TESTING_CONDITIONS(1e16+1 == 1e16);
	TESTING_CONDITIONS(1e20+1 == 1e20);
	
}
