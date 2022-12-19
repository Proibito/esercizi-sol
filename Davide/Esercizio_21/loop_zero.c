#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

/*
Non riesco a farlo funzionare correttamente.
I segnali arrivano talmente tanto di frequente che il padre non riesce a cambiare il valore del proprio var.
Se il suo valore di var non cambia nessun processo può terminare.
*/

void signal_handler (int signum );
/*
DA FARE
-Scrivere il loop di var nel processo padre
-Scrivere tutto il codice riguardante la consegna dal secondo punto in poi.
*/

int n_child, var=1, active_childs=0;
unsigned int *pid_list;

int main(int args, char * argv[])
{
    printf("Show PID Parent: %d\n", getpid());

    if(args<3)
    {
        fprintf(stderr, "Numero di argomenti passati in esecuzione non sufficienti\n");
        exit(-1);       /* credo sia come fare "return(-1);"  */
    }

    int i, max_number;
    int pid=1;
	sigset_t mask_SIGUSR1;
    struct sigaction sa_sigusr1;

    n_child = atol(argv[1]);
    max_number = atol(argv[2]);
    
    /* Setup vettore */
    pid_list = calloc(n_child, sizeof(pid));

    /*  Setup mask  */
    bzero(&sa_sigusr1, sizeof(sa_sigusr1));
    sa_sigusr1.sa_handler = signal_handler;
    sa_sigusr1.sa_flags = SA_NODEFER;
    sigemptyset(&mask_SIGUSR1);
    sigaddset(&mask_SIGUSR1, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &mask_SIGUSR1, NULL);
    sa_sigusr1.sa_mask = mask_SIGUSR1;
    
    sigaction(SIGUSR1, &sa_sigusr1, NULL);  /*  Assign handler to reaction when receiving SIGUSR1  */
    

    printf("Inizio creazione figli\n");
    for(i=0; i<n_child; i++)
    {
		switch(pid=fork())
        {
            case 0:     /*caso figlio */
                //printf("Creazione processo %d.\tDormo per 1 sec. Poi riprendo.\n", getpid());
                sleep(1);
                while(1)
                {
                    
                    var++;
                    if(var>=max_number)
                    {
                        var = var - max_number;
                    }
                    if(var==0)
                    {
                        //printf("Valore zero -> %d\n", getpid());
                        kill(getppid(), SIGUSR1);
                    }
                }
                printf("Non dovevo arrivare qui!! -- %d\n", getpid());
                break;

            default:        /* caso padre*/
                /* Prima di mettersi a contare con var deve aver creato tutti i figli */
                /*  Aggiunta PID del figlio alla lista  */
                pid_list[active_childs] = pid;
                active_childs++;
                break;
        }
	}

    /*  Activation of mask that activates handler  */
    sigprocmask(SIG_BLOCK, &mask_SIGUSR1, NULL);
    while(active_childs>0)
    {
        var++;
        if(var>=max_number)
        {
            var = var - max_number;
        }
        //printf("PADRE: var -> %d\n", var);
        if(var==0)
        {
            //printf("Coincidenza di zeri trovata!\n");
            sigprocmask(SIG_BLOCK, &mask_SIGUSR1, NULL);
        }
        else
        {
            sigprocmask(SIG_UNBLOCK, &mask_SIGUSR1, NULL);
        }
    }

    printf("Raggiunto il fondo del programma\n");
    return(1);

}


void signal_handler (int signum)
{
    int pid_pick;
    static int sigusr1_calls=0;
    sigusr1_calls++;

    //printf("Ricevuto il segnale %s", strsignal(signum));

    if(var == 0&&active_childs!=0)
    {
        pid_pick = rand()%active_childs;
        kill(pid_list[pid_pick], SIGTERM);
        active_childs--;
        printf("SIGTERM --> %d\n", pid_list[pid_pick]);
        pid_list[pid_pick] = pid_list[active_childs];
    }
    
}