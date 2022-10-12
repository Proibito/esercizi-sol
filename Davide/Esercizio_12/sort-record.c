#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 10
#define MIN_AGE 1
#define MAX_AGE 99
#define RAND_MAX 122-97

typedef struct
{
    char * name;
    int age;
} record;

record * rec_rand_create(int n)
{
    record elenco[n];
    int i, j=0;
    char stringa_generata[MAX_LEN+1];       //+1 per lo \0
    for(i=0;i<n;i++)
    {
        
        for(j=0;j<MAX_LEN;j++)
        {
            stringa_generata[j] = (char)(rand()+97);
        }
        stringa_generata[j+1] = '\0';

        elenco[n].age = rand()+MAX_AGE-MIN_AGE;
        elenco[n].name = stringa_generata;
    }
    return &elenco;
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
}