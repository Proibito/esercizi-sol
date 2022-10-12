#include <stdio.h>
#include <stdlib.h>

long *fibo(int n)
{
    int girovago = 0;
    long precedente = 0;
    long successivo = 1;
    long fibo = 0;
    long *ritorno = malloc(sizeof(long) * n);
    for (; girovago < n; girovago++)
    {
        if (girovago == 0)
        {
            ritorno[0] = precedente;
            continue;
        }

        precedente = successivo;
        successivo = fibo;
        fibo = precedente + successivo;
        ritorno[girovago] = fibo;
    }
    return ritorno;
}

int main()
{

    int numeriDiFibo = 5;
    long *array;

    array = fibo(numeriDiFibo);
    int i = 0;
    for (; numeriDiFibo > i; i++)
    {
        printf("%li\n", array[i]);
    }
    free(array);
}
