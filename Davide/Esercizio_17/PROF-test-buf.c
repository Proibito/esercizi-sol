#include <stdio.h>

/*
 * Prova a eseguire con
 * 
 * ./a.out
 * 
 * e con
 *
 * ./a.out > output-file
 *
 * Poi prova scrivere #if 0 e/o a scommentare setvbuf
 */

int main(int argc, char * argv[])
{
#if 0
	/* Set no buffering for stdout */
	setvbuf(stdout, NULL, _IONBF, 0);
#endif
#if 1
	fprintf(stdout, "Prima\n");
#else
	fprintf(stdout, "Prima");
#endif
	/* writing to the file descriptor 1 (stdout) */
	dprintf(1, "Dopo\n");
}
