#include<stdio.h>

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

    char s[100];
    long n;
    long vet[50];
    int pos_vet=0;
    fgets(s, sizeof(s), stdin);
    while(s!='\0')
    {
        if(strtol(s, null, 10)%2==1)
        {
            printf("%l", n);
        }
        else
        {
            vet[pos_vet] = 
            pos_vet++;
        }
        fgets(s, sizeof(s), stdin);
    }
    
    return 0;

}