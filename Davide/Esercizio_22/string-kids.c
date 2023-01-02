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

int main(int argc, char * argv[])
{
    if(argc<2)
    {
        dprintf(2, "Non ci sono abbastanza argomenti da linea di comando");
    }

    printf("PADRE: %d\n", getpid());

    int n_child = atol(argv[1]);
    int count_signaled, count_exited;
    /*int *pid_index = calloc(n_child, 4);*/   int pid_index[100];
    int i, child_status, pid_terminated;
    char *final_status = calloc(4*n_child, 4);  /* 4*n_child perchè ogni figlio occuperà al massimo 4 byte (3 per il numero e uno per lo spazio). */
    char *da_aggiungere = calloc(4, 1);       /* Ogni figlio occuperà al massimo 4 byte quindi 4 blocchi da 1 byte. */
    char * stringa_out;
    char *const args[] = {"./char-loop", "a", NULL};
    char *const envvar[] = {NULL};


    printf("Inizio creazione figli\n");
    for(i=0;i<n_child;i++)
    {
        pid_index[i] = fork();
        
        if(pid_index[i]==0)
        {
            //free(pid_index);         /* Se è un figlio non serve si ricordi la lista dei PID */
            
            execve("./char-loop", args, envvar);   /* Separazione verso char_loop */
            //n_child=0;      /* Per saltare questo for e il prossimo. */
            printf("Non dovrei arrivare qui.\n");
            exit(-1);
        }
        else
        {
            printf("Creazione processo #%d con PID %d\n", i, pid_index[i]);
        }
    }

    sleep(2);
    /* Dopo aver creato tutti i figli (e avergli dato del tempo per eseguire string-kids.c mando il segnale */

    for(i=0;i<n_child;i++)
    {
        kill(pid_index[i], SIGINT);
    }

    stringa_out = calloc(n_child+1, 1);

    i=0;
    while(wait(&child_status)!= -1)
    {
        if (WIFEXITED(child_status))
        {
			count_exited++;
            stringa_out[i++] = WEXITSTATUS(child_status);
        }
        if(WIFSIGNALED(child_status))
        {
            count_signaled++;
        }
    }
    printf("Numero figli correttamente usciti:\n%d/%d\n", count_exited, n_child);
    printf("Numero figli terminati prima di impostare l'handler di SIGINT:\n%d/%d\n", count_signaled, n_child);
    stringa_out[i]='\0';

    //if(n_child)
    printf("\nELENCO status:\n%s\n", stringa_out);
}