#include <stdio.h>
#include <string.h>

/*
 * This example reads the command line arguments and print all the
 * strings before and after being sorted.
 */

/*
 * Print the hex content of n bytes, starting from the address p in
 * memory.
 */
void dump_mem(void * p, unsigned int n);

/*
 * Function to sort strings according to alphabetic order
 */
void sort_strings(char* array_char_p[], int length);


int main(int argc, char *argv[])
{
	int i;
	char * p;

	/* Printing the number of arguments */
	printf( "argc = %d\n", argc);
	for(i=0; i<argc; ++i) {
		printf("argv[%d] = %p ==> \"%s\"\n", i, argv[i], argv[i]);
	}

	/* Now printing the memory content starting from argv[0] */
	p = argv[0];
	printf("\nPrinting the memory content from argv[0]");
	dump_mem(p,50);

	/* Now sorting */
	printf("Now sorting\n");
	sort_strings(argv, argc);

	/* Printing the number of arguments */
	printf( "argc = %d\n", argc);
	for(i=0; i<argc; ++i) {
		printf("argv[%d] = %p ==> \"%s\"\n", i, argv[i], argv[i]);
	}

	/* Now printing the memory content starting from argv[0] */
	printf("\nPrinting the memory content from argv[0]");
	dump_mem(p,50);
	
	return 0;
}

/*
 * Sorting the strings pointed by array_char_p by alphabetic order.
 * Strings are sorted by sorting the pointers they point to.
 */
void sort_strings(char* array_char_p[], int length)
{
	int i, j;
	char* tmp;
	for( i=0; i< length; i++ ) {
		for(j=i+1; j< length; j++) {
			if( strcmp(array_char_p[i], array_char_p[j]) > 0 ) {
				tmp = array_char_p[i];
				array_char_p[i] = array_char_p[j];
				array_char_p[j] = tmp;
			}
		}
	}
}

void dump_mem(void * p_in, unsigned int n)
{
	unsigned int i;
	unsigned char *p;

	p = (unsigned char *)p_in;
	printf("\np=%p\n", p);
	/* if the last hex digit of p is not 0... */
	if ((long)p & 0xF) {
		/*
		 * ...need to print some heading space
		 *
		 * (void *)((long)p & -15) is
		 *    the address p with last hex digit set = 0x0
		 */
		printf("(%p)", (void *)((long)p & -15));
		for (i=0; i<((long)p & 0xF); i++) {
			printf("   ");
		}
	}
	/* printing 16 bytes per row */
	for (i=0; i<n; i++, p++) {
		/* print the address at the begin of each row */
		if (!(((long)p & 0xF))) {
			printf("(%p)", p);
		}
		/* print the byte */
		printf(" %02X", (unsigned char)*p);
		/* new line if last byte of the row */
		if (((long)p & 0xF) == 0xF) {
			printf("\n");
		}
	}
	printf("\n\n");
}
