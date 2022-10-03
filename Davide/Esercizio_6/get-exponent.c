#include<stdio.h>
#include<math.h>
#include <string.h>

// ti sto modificando il file


// ecco qui

int main()
{
    double n;
    int i;
    // posizione;
    int p_esponente;
    int esponente=0;
    int intero=0;
    printf("Inserisci il numero con la virgola: ");
    scanf("%lf", &n);

    memcpy(&intero, ((char*)&n+6), 2);
    printf("Intero = %4x\n", intero);
    intero &= 0x7FFF;
    intero = intero>>4;
    printf("Intero (dopo shift) = %4x\n", intero);

    /*esponente = *((char*)&n+6);
    esponente = esponente<<2;
    esponente = esponente>>32;*/

    //dovrebbe adesso puntare alla zona dell'esponente


    printf("Esponente = %d\tIndirizzo = %p", esponente, &esponente);

    //printf("\nINDIRIZZI\nposizione = %p\nesponente = %p\nesponente+8*8 = %p\n\nCONTENUTI\n(pre-modifica)\t esponente = %li", &n+1, &esponente, &esponente+8*8, esponente);
    //memcpy(&esponente+8*8, &n+1, 11);
    //printf("\n(post-modifica)\t esponente = %li", esponente);

    //printf("Esponente = %lf\n", esponente);

    printf("\nEsponente = %d\n", esponente);

    return 0;
}