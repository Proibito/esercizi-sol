#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(int args, char * argv[])
{
    int n_write, n_kids, i, j, child_pid, status;
    FILE * fp_output;

    n_kids=atol(argv[2]);
    n_write=atol(argv[3]);
    
    
    fp_output = fopen(argv[1], "w");

    for(i=0;i<n_kids;i++)
    {
        switch (child_pid = fork())
        {
        case 0:     /*figlio*/
            for(j=0; j<n_write; j++)
            {
                fprintf(fp_output, "%d figlio di %d\t", getpid(), getppid());
            }
            fprintf(fp_output, "\n");
            exit(i);
            break;
        
        case -1:     /*errore*/
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        default:    /*padre*/
            
            break;
        }
    }

    while((child_pid = wait(&status))!=-1)  /* Fino a che ho figli*/
    {
        printf("PID = %5d (PARENT): Got info of child with PID = %d, status = 0x%04X\n", getpid(), child_pid, status);
    }   

    if(errno == ECHILD)
    {
        printf("PID %6d got no more child processes\n", getpid());
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "Error #%d: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    fclose(fp_output);
}