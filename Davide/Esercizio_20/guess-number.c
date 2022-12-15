#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

void handle_signal(int signal);

/*
EXECUTE WITH:
gcc guess-number.c
./a.out 20 20
*/

int main(int args, char * argv[])
{
    int pick, guess;
    struct sigaction sa;

    /*  CHECK ARG  */
    if(args<2)
    {
        fprintf(stderr, "Numero di argomenti passati in esecuzione non sufficienti\n");
        exit(-1);       /* credo sia come fare "return(-1);"  */
    }


    /*  PID print   */
    printf("My pid is: %d\n", getpid());

    /*  SA setup*/
    bzero(&sa, sizeof(sa));
    sa.sa_handler = handle_signal;
    sigaction(SIGALRM, &sa, NULL);

    srand(time(0));        /*  forse si può sostituire getpid() con time()  */
    pick = rand()%((atol(argv[1])+1));

    alarm(atol(argv[2]));

    while(1)
    {
        scanf("%d", &guess);
        if(pick==guess)
        {
            printf("OTTIMO! Hai indovinato!\n");
            break;
        }
        else
        {
            if(pick<guess)
            {
                printf("MINORE\t");
            }
            else
            {
                printf("MAGGIORE\t");
            }
        }
    }

}

void handle_signal(int signal)
{
    printf("\nTempo scaduto\n");
    exit(2);
}