#include<stdio.h>
#define LUNGH 7     //perchè la stringa è fatta da 7 numeri

//-----COMPLETO E FUNZIONANTE-----//
//poco ottimizzato

int main()
{

    /*
        -ricezione della stringa da input
        -riconoscimento numeri e salvataggio in un vettore
        -rilettura del vettore e stampa dei numeri dispari
        -rilettura del vettore e stampa dei numeri pari

        VERSIONE ALTERNATIVA
        -ricezione della stringa numero per numero
        -
    */

    /*
    VECCHIA VERSIONE
    char stringa[100];
    long n;
    long vet[50];
    int pos_vet=0;
    fgets(stringa, sizeof(stringa), stdin);
    while(stringa!='\0')
    {
        if(strtol(stringa, null, 10)%2==1)
        {
            printf("%l", n);
        }
        else
        {
            vet[pos_vet] = 
            pos_vet++;
        }
        fgets(stringa, sizeof(stringa), stdin);
    }
    
    return 0;
    */
   
    char stringa[100];
    long n[LUNGH];
    printf("Inserisci i numeri da stampare:\n");
    for(int i=0;i<LUNGH;i++)
    {
        fgets(stringa, sizeof(stringa), stdin);
        n[i] = strtol(stringa, NULL, 10);
    }

    for(int i=0;i<LUNGH;i++)
    {
        if(n[i]%2==1)
            printf("%ld ", n[i]);
    }
    for(int i=0;i<LUNGH;i++)
    {
        if(n[i]%2==0)
            printf("%ld ", n[i]);
    }

    //Risolto in modo poco ottimizzato ma risolto

    printf("\n");
    return 0;
}