#include <stdio.h>     /* for printf(), fgets() functions */
#include <stdlib.h>    /* for strtol(), atof() functions  */
#include <string.h>    /* for strlen() */

int main()
{
	char s[10];
	int a, b;
	double f;

	/* reading an integer input */
	printf("Enter an integer\n", %s);
	fgets(s, sizeof(s), stdin);
	printf("s=\"%s\", strlen(s)=%d, sizeof(s)=%d\n", s, (int)strlen(s), (int)sizeof(s));
	printf("Printing the entire s[10]\n");
	printf("Decimal:     %d %d %d %d %d %d %d %d %d %d\n", s[0], s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9]);
	printf("Hexadecimal: %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X\n", s[0], s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9]);
	a = strtol(s, NULL, 10);

	/* reading a second integer input */

	printf("\nEnter a second integer\n");
	fgets(s, sizeof(s), stdin);
	printf("s=\"%s\", strlen(s)=%d, sizeof(s)=%d\n", s, (int)strlen(s), (int)sizeof(s));
	b = strtol(s, NULL, 10);
	printf("%i + %i = %i\n", a, b, a + b);
	printf("Printing the entire s[10], after second read\n");
	printf("Decimal:     %d %d %d %d %d %d %d %d %d %d\n", s[0], s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9]);
	printf("Hexadecimal: %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X\n", s[0], s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9]);

	/* reading an integer input */
	printf("\nNow enter a floating point number\n");
	fgets(s, sizeof(s), stdin);
	printf("s=\"%s\", strlen(s)=%d, sizeof(s)=%d\n", s, (int)strlen(s), (int)sizeof(s));
	f = atof(s);
	printf("Value read written as %%f=%f and %%e=%e\n", f, f);
	printf("Printing the entire s[10], after third read\n");
	printf("Decimal:     %d %d %d %d %d %d %d %d %d %d\n", s[0], s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9]);
	printf("Hexadecimal: %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X\n", s[0], s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9]);
	return 0;
}
