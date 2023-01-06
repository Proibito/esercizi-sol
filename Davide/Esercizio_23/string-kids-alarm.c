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

//#define SET_LIMIT_TO_N_PROCESS
#define LIMIT 10

void handler_custom (int signum);

int *pid_index, n_child, n_extra_child = 0;

int main(int argc, char * argv[])
{
    if(argc<2)
    {
        dprintf(2, "Non ci sono abbastanza argomenti da linea di comando");
    }

    printf("PADRE: %d\n", getpid());

    n_child = atol(argv[1]);
    int count_signaled, count_exited;
    pid_index = calloc(n_child, 4);  /*  int pid_index[100];  */
    int i, j, child_status, pid_terminated, sum_status=0, pid_pick, counter_child_exited=0;
    char * stringa_out;

    struct sigaction sa_SIGALRM;                //creo il sigaction
    bzero(&sa_SIGALRM, sizeof(sa_SIGALRM));     //"pulisco" il sigaction
    sa_SIGALRM.sa_handler = handler_custom;     //assegno il custom handler al mio sigaction
    sigaction(SIGALRM, &sa_SIGALRM, NULL);      //assegno il sigaction al segnale

    char *const args[] = {"./char-loop", "a", NULL};
    char *const envvar[] = {NULL};

    

    printf("Inizio creazione figli\n");
    for(i=0;i<n_child;i++)
    {
        pid_index[i] = fork();
        
        if(pid_index[i]==0)
        {
            //free(pid_index);
            
            execve("./char-loop", args, envvar);   /* Separazione verso char_loop */
            printf("Non dovrei arrivare qui - %d\n", __LINE__);
            exit(-1);
        }
        else
        {
            printf("Creazione processo #%d con PID %d\n", i, pid_index[i]);
        }
    }
    printf("Figli creati correttamente\n\n");

    /*
    Tutti i figli sono stati creati.
    Il vettore pid_index è stato riempito dei PID dei n_childs figli.
    */

    j=0;
    stringa_out = calloc(n_child+n_extra_child+1, 1);
    alarm(3);
    while(1)
    {
        do
        {
            pid_terminated = wait(&child_status);
            //printf("Wait interrotta: %d\n", errno);
        }
        while(pid_terminated==-1);
        
        if (WIFEXITED(child_status))
        {
            //printf("Figlio %d uscito correttamente\n", pid_terminated);
            counter_child_exited++;
        }
        else
        {
            printf("Problema nella exit del figlio %d\n", pid_terminated);
            //exit(-3);
        }
        stringa_out[j] = WEXITSTATUS(child_status);
        //stampa
        j++;
        sum_status = (sum_status + WEXITSTATUS(child_status))%256;
        printf("Aggiungo %d\tSUM = %d\n", WEXITSTATUS(child_status), sum_status);
        
        // RICERCA PID MORTO
        for(i=0; pid_index[i]!=pid_terminated; i++);
        if(i>n_child)
        {
            printf("PID processo %d non trovato nell'elenco.\n", pid_terminated);
            sum_status=0;
        }
        pid_pick = i;

        #ifdef SET_LIMIT_TO_N_PROCESS
            if(n_extra_child>LIMIT)
            {
                sum_status=0;
            }
        #endif

        if(sum_status == 0)
        {
            printf("\n------------------------------\n");
            for(i=0; i<n_child; i++)
            {
                if(i!=pid_pick)
                {
                    kill(pid_index[i], SIGTERM);
                    pid_terminated = wait(&child_status);
                    printf("Terminato processo %d\n", pid_index[i]);
                }
            }
            
            /*for(i=0;wait(&child_status)!= -1;i++)
            {
                printf("Terminato processo %d\n", pid_index[i]);
                stringa_out[j++] = WEXITSTATUS(child_status);
            }*/
            stringa_out[j++] = '\0';
            break;
        }
        else
        {
            n_extra_child++;
            printf("Allungamento a +%d\n\n", n_extra_child);
            stringa_out = realloc (stringa_out, n_child + n_extra_child + 1);
            
            pid_index[pid_pick] = fork();
            if(pid_index[pid_pick]==0)
            {
                free(stringa_out);
                execve("./char-loop", args, envvar);   /* Separazione verso char_loop */
                printf("Non dovrei arrivare qui - %d\n", __LINE__);
                exit(-2);
            }
            else
            {
                printf("Creazione processo #%d - %d\n", n_child + n_extra_child, pid_index[pid_pick]);
                alarm(1);
            }
        }
    }
    printf("Stringa finale: %s\nSomma degli status finale: %d\nFigli usciti terminati %d/%d\n", stringa_out, sum_status, counter_child_exited+n_child, n_child+n_extra_child+1);
    printf("------------------------------\n");
    free(stringa_out);
    free(pid_index);
    return 0;
}

void handler_custom(int signum)
{
    srand(time(NULL));
    if(signum == SIGALRM)
    {
        int pid_pick = rand()%n_child;
        kill(pid_index[pid_pick], SIGINT);
    }
    else
    {
        printf("Uscita a causa di %d\n", signum);
        exit(-1);
    }
}