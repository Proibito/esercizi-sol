#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <strings.h>

/* 
 * Try by defining the symbol at compile time with
 * (1) gcc ...
 * (2) gcc -DWIDE_DATA_MEM ...
 * (3) gcc -S -g -O0 ...
 */

/* #define WIDE_DATA_MEM */
/* #define MASK_SIGALRM */

/*
 * The global variable "memory" is used to check if operations are
 * atomic or not
 */
#ifdef WIDE_DATA_MEM
struct two_words {double a, b; };
#else
struct two_words {char a, b; };
#endif

/*
 * Declaring a global variable to be written by the main code and read
 * by the handler every second.
 */
struct two_words memory;

/*
 * The handler prints the current content of the "memory" global
 * variable
 */
void handler(int signum)
{
	printf (
	#ifdef WIDE_DATA_MEM
			"%f,%f %s\n",
	#else
			"%d,%d %s\n",
	#endif
			memory.a, memory.b, (memory.a==memory.b) ? "OK" : "!!");
		alarm (1);
}

int main (void)
{
	struct sigaction sa;
	static struct two_words zeros = { 0, 0 }, ones = { 1, 1 };
	sigset_t my_mask, old_mask;
	
	memory = zeros;

	/* Setup the SIGALRM handler */
	bzero(&sa, sizeof(sa));
	sa.sa_handler = &handler;
	sigaction(SIGALRM, &sa, NULL);
	alarm (1);

	#ifdef MASK_SIGALRM
		/* Set a mask with SIGALRM */
		sigaddset(&my_mask, SIGALRM);
	#endif

		/*
		* Write forever {0,0}, then {1,1}, then {0,0}... in global
		* variable memory
		*/
		while (1)
		{
			#ifndef MASK_SIGALRM
					/* SIGALRM may arrive "in the middle" of each assignment */
					memory = zeros;
					memory = ones;
			#else
					/* SIGALRM may NOT arrive "in the middle" of each assignment */
					sigprocmask(SIG_BLOCK, &my_mask, &old_mask);
					memory = zeros;
					sigprocmask(SIG_SETMASK, &old_mask, NULL);
					sigprocmask(SIG_BLOCK, &my_mask, &old_mask);
					memory = ones;
					sigprocmask(SIG_SETMASK, &old_mask, NULL);
			#endif
		}
}

