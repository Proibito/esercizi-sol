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

int create_process(int * pid_index, int n_children);

int main(int argc, int *argv[])
{
    int *pid_index, *pipe_index;
    int n_children = atol(argv[1]);
    int max_number = atol(argv[2]);
    int i, process_number, number, pick;
    int read_pipe, write_pipe;
    /*
    -Ricezione dei dati da argv
    -Creazione pipe
    -Creazione processi con fork
    -Identificazione pipe di read e write del processo
    -Chiusura delle pipe non usate
    -Avvio delle read su tutti i figli
    -Generazione numero casuale da scrivere
    -Prima write dal processo padre
    -Ripetizione del ciclo read-decrease-write fino a quando il numero letto è zero
     A quel punto faccio la write di zero
    -Quando ho finito il ciclo vado a chiudere le pipe di read e write attive
    -Exit
    */
    
    pid_index = calloc(n_children, sizeof(*pipe_index));      //creo vettore di n_children elementi di tipo int
    pipe_index = calloc(2*n_children, sizeof(*pipe_index));

    // CREAZIONE PIPE
    for(i=0; i<n_children; i++)
        pipe(pipe_index+2*i);
    
    // CREAZIONE PROCESSI
    process_number = create_process(pid_index, n_children);

    // PRESENTAZIONE PROCESSI
    if(process_number==-1)
    {
        dprintf(1, "PRESENTAZIONE PROCESSI\n");
        for(i=0;i<n_children;i++)
            dprintf(1, "%d figlio numero %d\n", pid_index[i], i);
    }

    // INDENTIFICAZIONE DELLE PIPE DI READ E WRITE DEL PROCESSO
    if(process_number != -1)
    {           //  FIGLI
        read_pipe = pipe_index[process_number*2];
        if(process_number != (n_children-1))      // Caso di ultimo processo
            write_pipe = pipe_index[process_number*2+3];
        else
            write_pipe = pipe_index[1];
    }
    else
    {           //  PADRE
        write_pipe = pipe_index[1];     //posizione iniziale di write
    }

    //CHIUSURA PIPE NON UTILIZZATE
    for(i=0; i<n_children*2; i++)
    {
        if(process_number != -1)
        {       // Se figlio
            if(pipe_index[i]!=read_pipe && pipe_index[i]!=write_pipe)
            {
                close(pipe_index[i]);
            }
        }
        else
        {       // Se padre
            if(pipe_index[i]!=write_pipe)
            {
                close(pipe_index[i]);
            }
        }
    }

    // CICLO DI READ-DECREASE-WRITE
    if(process_number!=-1)
    {
        while(1)
        {
            read(read_pipe, &number, sizeof(max_number));
            dprintf(1, "%d - Ho letto il numero %d\n", getpid(), number);
            if(number!=0)
            {
                number--;
                write(write_pipe, &number, sizeof(max_number));
            }
            else
            {
                write(write_pipe, &number, sizeof(max_number));
                break;
            }
        }
        close(read_pipe);
        close(write_pipe);
        exit(EXIT_SUCCESS);
    }
    else
    {
        srand(getpid());
        pick = rand()%max_number+1;
        write(write_pipe, &pick, sizeof(max_number));
        dprintf(1, "Processo avviato con il numero %d\n", pick);
        exit(EXIT_SUCCESS);
    }
}

/*   Creazione dei processi con ritorno #n figlio   */
int create_process(int * pid_index, int n_children)
{
    int i;
    for(i=0; i<n_children; i++)
    {
        pid_index[i] = fork();
        if(pid_index[i] == 0)
        {
            free(pid_index);
            return i;
        }
        
    }
    return -1;
}