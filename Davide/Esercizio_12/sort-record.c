#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 15
#define MIN_AGE 1
#define MAX_AGE 99

typedef struct
{
    char * name;
    int age;
} record;

record * rec_rand_create(int n)
{
    record *elenco = malloc(sizeof(record)*n);
    int i, j=0;
    
    for(i=0;i<n;i++)
    {
        int lunghezza_stringa_generata = (rand()%MAX_LEN)+1;
        //char stringa_generata[lunghezza_stringa_generata];
        elenco[i].name = malloc(sizeof(char)*(lunghezza_stringa_generata+1));
        //printf("\nLunghezza stringa %d: %d oppure %d o anche %d", i, strlen(stringa_generata), sizeof(*stringa_generata)/sizeof(char), lunghezza_stringa_generata);
        for(j=0;j<lunghezza_stringa_generata;j++)
        {
            elenco[i].name[j]= (char)(rand()%25+97);
        }
        elenco[i].name[j] = '\0';
        //printf("\nStringa: %s\n", elenco->name);

        elenco[i].age = rand()%(MAX_AGE-MIN_AGE)+MIN_AGE;
        //elenco[i].name = stringa_generata;
    }
    return elenco;
}

void rec_sort(record * v, int n)    //ordina gli elementi dell’array v di lunghezza n secondo il campo age crescente
{
    int i, j, tutto_a_posto=0;
    for(j=0;j<n-1;j++)
    {
        for(i=0;i<n-1;i++)
        {
            if(v[i].age>v[i+1].age)
            {
                printf("\nScambia %d e %d\n", v[i].age, v[i+1].age);
                swap(&v[i], &v[i+1]);
            }
        }
    }
}

void swap(record *a, record *b)
{
    record temporaneo;

    temporaneo = *a;
    *a = *b;
    *b = temporaneo;
}

int main()
{
    int numero;
    char stringa_input[100];
    printf("\nInserisci un numero: ");
    fgets(stringa_input, sizeof(stringa_input), stdin);
    numero = strtol(stringa_input, NULL, 10);

    record * elenco;
    elenco = rec_rand_create(numero);

    int i;
    printf("\nElenco");
    for(i=0;i<numero;i++)
    {
        printf("\nElemento %d\tNome: %s\t\tEta': %d", i, elenco[i].name, elenco[i].age);
    }

    rec_sort(elenco, numero);

    printf("\n\nElenco ordinato");
    for(i=0;i<numero;i++)
    {
        printf("\nElemento %d\tNome: %s\t\tEta': %d", i, elenco[i].name, elenco[i].age);
    }

    printf("\n");
    return 0;
}