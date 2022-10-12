#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long * fibo(int n)
{
    long * p;
    int puntatore = 2;
    p=malloc(n*sizeof(*p));
    if(n<=0)        //caso con n=0 non accettabile
    {
        printf("La dimensione del vettore non e' accettabile.\nTerminazione programma anticipata.\n");
        return NULL;
    }

    if(n>0)
    {
        p[0] = 0;
        if(n>1)
        {
            p[1] = 1;
        }
    }

    while (puntatore < n)
    {
        p[puntatore] = p[puntatore-1]+p[puntatore-2];
        puntatore++;
    }
    

    return p;
    
}



int main()
{
    //      INPUT       //

    int n, i;
    long * vet;
    char stringa_input[100];
    printf("Inserisci quanti numeri di Fibonacci vuoi ricevere: ");
    fgets(stringa_input, sizeof(stringa_input), stdin);
    n = strtol(stringa_input, NULL, 10);

    //      CHIAMATA FUNZIONE       //

    vet = fibo(n);
    
    //      STAMPA VETTORE      //

    for(i=0;i<n;i++)
    {
        printf("%li\n", vet[i]);
    }

    free(vet);
}