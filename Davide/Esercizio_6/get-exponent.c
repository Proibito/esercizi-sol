#include<stdio.h>
#include<math.h>
#define MASK 2146435072

// ti sto modificando il file


// ecco qui

int main()
{
    double n;
    int i;
    double esponente;
    printf("Inserisci il numero con la virgola: ");
    scanf("%lf", &n);

    esponente = n|MASK;      //numero ricavato dalla disposizione dei bit che permette di avere il bit più significativo a zero, 11 uno e il resto zero.

    printf("Esponente = %lf\n", esponente);

    return 0;
}