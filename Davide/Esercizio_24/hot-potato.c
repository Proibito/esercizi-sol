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
int offset(int rig, int col, int n_children);       //non usata

int main(int argc, char * argv[])
{
    int *pid_index, *pipe_index;
    int n_children = atol(argv[1]);
    int max_number = atol(argv[2]);
    int process_number, i, pick, last_was_zero=0, pipe_read, pipe_write;
    int n_byte_written;
    
    int buff;

    srand(time(NULL));
    pick = (rand()%max_number)+1;

    printf("Ricevuti:\n%d\t= n_children\n%d\t= max_number\n%d\t= pick\n", n_children, max_number, pick);

    pid_index = calloc(n_children, sizeof(*pipe_index));      //creo vettore di n_children elementi di tipo int

    pipe_index = calloc(2*n_children, sizeof(*pipe_index));
    //pipe_index[0] = calloc(n_children, sizeof(*pipe_index));    //vettore dei read
    //pipe_index[1] = calloc(n_children, sizeof(*pipe_index));    //vettore dei write

    /*   CREAZIONE PIPE   */
    for(i=0; i<n_children; i++)
        pipe(pipe_index+2*i);

    /*   -----FORK-----   */
    process_number = create_process(pid_index, n_children);
    if(process_number==-1)      //Se padre...
    {
        n_byte_written = write(pipe_index[1], &pick, sizeof(*pipe_index));     //Scrivo il numero a caso nella prima pipe.
        printf("%d byte scritti\n", n_byte_written);
        /*{
            printf("Problema nella write\n");
        }*/

        pipe_write = pipe_index[0];
        for(i=0; i<2*n_children; i++)     //   Chiusura delle pipe non usate dal padre
            if(pipe_index[i]!=pipe_write)
                close(pipe_index[2*i]);
        //read(pipe_index[n_children-2], &buff, sizeof(*pipe_index));      Il padre non legge
        
        printf("\nDall'ultima pipe esce %d\n", buff);
        
        exit(1);
    }
    else                        // Se figlio...
    {
        pipe_read = pipe_index[process_number];
        if(process_number==n_children-1)
        {
            pipe_write = pipe_index[1];
        }
        else
        {
            pipe_write = pipe_index[process_number+3];
        }

        for(i=0; i<2*n_children; i++)    //  Chiusura delle pipe non utilizzate dal processo
        {
            if(pipe_index[2*i]!=pipe_write && pipe_index[2*i]!=pipe_read)
                close(pipe_index[2*i]);
        }

        while(last_was_zero==0)
        {    
            read(pipe_read, &buff, sizeof(*pipe_index));
            printf("%d -> leggo e trasmetto %d\n", getpid(), buff);
            if(process_number==n_children-1)   //Se punti all'ultimo 
            {
                if(buff==0)
                {
                    write(pipe_write, &buff, sizeof(*pipe_index));
                    last_was_zero=1;
                }
                else
                {
                    buff = buff-1;
                    write(pipe_write, &buff, sizeof(*pipe_index));
                }
            }
            else
            {
                if(buff==0)
                {
                    write(pipe_write, &buff, sizeof(*pipe_index));
                    last_was_zero=1;
                }
                else
                {
                    buff = buff-1;
                    write(pipe_write, &buff, sizeof(*pipe_index));
                }
            }
        }
        close(pipe_read);
        close(pipe_write);
        exit(1);
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

int offset(int rig, int col, int n_children)
{
    return rig*n_children+col;
}