#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define TEST_ERROR    if (errno) {fprintf(stderr, \
					   "%s:%d: PID=%5d: Error %d (%s)\n",\
					   __FILE__,\
					   __LINE__,\
					   getpid(),\
					   errno,\
					   strerror(errno));}

void signal_handler (int signum );

int n_child, var=1, active_childs=0;
pid_t *pid_list;

int main(int args, char const* argv[])
{
    printf("Show PID Parent: %d\n", getpid());
    srand(time(NULL));

    if(args<3)
    {
        fprintf(stderr, "Numero di argomenti passati in esecuzione non sufficienti\n");
        exit(-1);       /* credo sia come fare "return(-1);"  */
    }

    int i, max_number;
    int pid=1;
    struct sigaction sa_sigusr1;

    n_child = atol(argv[1]);
    max_number = atol(argv[2]);
    
    /* Setup vettore */
    pid_list = calloc(n_child, sizeof(pid_t));

    bzero(&sa_sigusr1, sizeof(sa_sigusr1));
    sa_sigusr1.sa_handler = SIG_IGN;        /* Per ora ignora il segnale. */
    sigaction(SIGUSR1, &sa_sigusr1, NULL);
    

    printf("Inizio creazione figli\n");
    for(i=0; i<n_child; i++)
    {
		TEST_ERROR;
	    pid_list[i] = fork();
		TEST_ERROR;
        if(pid_list[i] == 0)
        {       /* Caso figlio */
                free(pid_list);
                n_child = 0;        /* Per uscire dal for al prossimo giro */
        }
	}

    if(active_childs)
    {       /* Attivazione di SIGUSR1*/
        sa_sigusr1.sa_handler = signal_handler;
        sigaction(SIGUSR1, &sa_sigusr1, NULL);
    }

    for(var = 0; 1; var++)
    {
        if(var > max_number)
        {
            var = 0;
            if(!active_childs)
            {
                kill(getppid(), SIGUSR1);
            }
        }
    }

    printf("Raggiunto il fondo del programma\n");
	free(pid_list);
    return(1);

}


void signal_handler (int signum)
{
    int pid_pick;

    static int sigusr1_calls=0;     /* Per contare quante chiamate ho fatto */
    sigusr1_calls++;

    //printf("Ricevuto il segnale %s", strsignal(signum));

    if(var == 0)
    {
        pid_pick = rand()%active_childs;
        if(kill(pid_list[pid_pick], SIGTERM)!= -1)
        {
            if(waitpid(pid_list[pid_pick], NULL, 0) == -1)
            {
				write(1, "Errore durante SIGTERM\n", 23);		//printf("Errore durante SIGTERM\n");
            }
            pid_list[pid_pick] = pid_list[active_childs-1];
            active_childs--;
            printf("%d  said SIGTERM --> %d\n", pid_list[pid_pick], getpid());
			write(1, "%d said SIGTERM --> %d\n", pid_list[pid_pick], getpid(), sizeof((int)pid_list[pid_pick])+19+sizeof((int)getpid()));
        }
    }
    if(active_childs == 0)
    {
        exit(0);
    }
}