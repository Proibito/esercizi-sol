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
    int number = atol(argv[2]);
    int output_number;
    int * pipe_array;
    pipe_array = calloc(2, sizeof(*pipe));

    pipe(pipe_array);

    write(pipe_array[1], &number, sizeof(*pipe_array));
    read(pipe_array[0], &output_number, sizeof(*pipe_array));

    printf("Nella pipe è stato comunicato il numero %d\n", output_number);
    return 0;
}