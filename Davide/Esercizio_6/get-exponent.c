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
    int esponente_dec;
    printf("Inserisci il numero con la virgola: ");
    scanf("%lf", &n);

    memcpy(&intero, ((char*)&n+6), 2);      //copio i bit della porzione di memoria che mi interessa e li metto nella variabile intero.
    printf("Intero = %4x\n", intero);       //stampo intero prima di aver rimosso i bit che non mi interessano
    intero &= 0x7FFF;                       //uso una maschera per rimuovere il primo bit del segno
    intero = intero>>4;                     //shift a destra di 4 posizioni in modo da eliminare i bit della mantissa rimanenti
    printf("Intero (dopo shift) = %4x\ndecimale -> %d", intero, intero-1023);  //stampa

    /*esponente = *((char*)&n+6);
    esponente = esponente<<2;
    esponente = esponente>>32;*/

    //dovrebbe adesso puntare alla zona dell'esponente


    //printf("Esponente = %d\tIndirizzo = %p", esponente, &esponente);

    //printf("\nINDIRIZZI\nposizione = %p\nesponente = %p\nesponente+8*8 = %p\n\nCONTENUTI\n(pre-modifica)\t esponente = %li", &n+1, &esponente, &esponente+8*8, esponente);
    //memcpy(&esponente+8*8, &n+1, 11);
    //printf("\n(post-modifica)\t esponente = %li", esponente);

    //printf("Esponente = %lf\n", esponente);

    printf("\nEsponente = %d\n", esponente);
    //Elaboro esponente per renderlo decimale

    //esponente_dec=esponente_dec-1024;

    return 0;
}