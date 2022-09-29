#include<stdio.h>
#include<string.h>
#define NUMERI 10

int main()
{
    char stringa[100];
    int vettore[NUMERI];
    int i;
    FILE* fp = fopen("dati_input.txt", "r");
    //scanf("%d %d %d %d %d %d %d %d %d %d", &v[0], &v[1], &v[0], ...);
    printf("Inserisci i numeri:\n");
    for(i=0;i<NUMERI;i++)
    {
        fgets(stringa, sizeof(stringa), fp);

        vettore[i] = strtol(stringa, NULL, 10);

        printf("Salvato nel vettore: %d\n", vettore[i]);
    }

//    VETTORE RICEVUTO   //
    printf("\nVettore ricevuto:\n");
    for(i=0;i<NUMERI;i++)
    {
        printf("%d\n", vettore[i]);
    }

    int somma=0;
    int vettore_2[NUMERI];
    for(i=NUMERI-1;i>=0;i++)
    {
        vettore_2[i]=somma+vettore[i];
        somma = somma + vettore[i];
    }

    fclose(fp);
    return 0;
}