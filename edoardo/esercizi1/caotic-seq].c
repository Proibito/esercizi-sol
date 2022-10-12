#include <stdio.h>

// Si consideri la successione generata dal numero n e che calcola il numero successivo come segue:
// • se n `e pari allora il prossimo numero `e la met`a di n
// • se n `e dispari allora il prossimo numero `e il triplo pi`u uno.
// La sequenza termina quando si raggiunge 1. Si scriva un programma che, accettato un valore numerico intero N da tastiera,
// stampi la lunghezza di tutte le sequenze generate per ciascun valore di partenza della sequenza minore o uguale a N.

int peppino(int numero, int *contatore)
{
    if (numero == 1)
    {
        return numero;
    }

    if (numero % 2 == 0)
    {

        numero = numero / 2;
    }
    else
    {
        numero = (numero * 3) + 1;
    }
    *contatore = *contatore + 1;
    // printf("numero: %d\n", *contatore);
    return peppino(numero, contatore);
}

int main()
{
    int valore = 56;
    int contatore = 0;
    peppino(valore, &contatore);
    printf("giri fatti: %d \n", contatore);
}