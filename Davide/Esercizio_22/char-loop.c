#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler_custom (int signum);

int car;

int main(int argc, char * argv[])
{
    //printf("Il mio PID e' %d\n", getpid());
    //printf("Stampo la prima parte...");
    if(argc<2)
    {
        printf("Errore: numero di argomenti non sufficiente\n");
        return(-1);
    }
    //printf("... e stampo la seconda.\n");

    

    struct sigaction sa_SIGINT;
    bzero(&sa_SIGINT, sizeof(sa_SIGINT));
    //sa_SIGINT.sa_handler = SIG_IGN;         Per ora ignora il segnale. 
    //sigaction(SIGINT, &sa_SIGINT, NULL); 
    sa_SIGINT.sa_handler = handler_custom;
    sigaction(SIGINT, &sa_SIGINT, NULL);

    car = argv[1][0];

    for(;1;car++)
    {
        if(car>126)
        {
            car = 33;
        }
    }
}

void handler_custom(int signum)
{
    if(signum == SIGINT)
    {
        printf("Status processo %d = %d\n", getpid(), car);
        exit(car);
    }
    else
    {
        exit(-1);
    }
}