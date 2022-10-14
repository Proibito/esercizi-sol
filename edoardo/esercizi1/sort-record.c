#include <stdio.h>
#include <stdlib.h>
#define MIN_AGE 5
#define MAX_AGE 20
#define MAX_LEN 10

typedef struct
{
    char *name;
    int age;
} record;

record *rec_rand_create(int n)
{
    record *ritorno = malloc(sizeof(record) * n);
    int i = 0;
    for (; i < n; i++)
    {
        int lunghezzaStringa = (rand() % (MAX_LEN - 1) + 1) + 1;
        ritorno[i].name = malloc(sizeof(char) * lunghezzaStringa);
        // Inzializzo la stringa
        int k = 0;
        for (; k < lunghezzaStringa - 1; k++)
        {
            ritorno[i].name[k] = rand() % (90 - 65 + 1) + 65;
        }
        ritorno[i].name[lunghezzaStringa - 1] = '\0';

        ritorno[i].age = rand() % (MAX_AGE - MIN_AGE + 1) + MIN_AGE;
        if (i == 1)
        {
            ritorno[i].name = "questo";
            continue;
        }
        // ritorno[i].name = randomStringa;
        // del
    }
    return ritorno;
}

void swap(record *prima, record *dopo)
{
    record temp = *prima;
    *prima = *dopo;
    *dopo = temp;
}

void rec_print(record *v, int n)
{
    int i = 0;
    for (; i < n; i++)
    {
        printf("stringa casuale: %s, numero casuale: %d\n", v[i].name, v[i].age);
    }
}

void rec_sort(record *v, int n)
{
    int i = 0;
    for (; i < n; i++)
    {
        int minIndx = i;
        int k = i;
        for (; k < n; k++)
        {
            // printf("vk %d, vmin %d\n", v[k].age, v[minIndx].age);
            if (v[k].age < v[minIndx].age)
            {
                printf("min %d\n", v[k].age);
                minIndx = k;
            }
        }
        swap(&v[minIndx], &v[i]);
    }
}

void rec_free(record *v, int n)
{
    int i = 0;
    // for (; i < n; i++)
    // {
    // free(v[i].name);
    // }
    free(v);
}

int main()
{
    record *prova;
    int lunghezza = 15;
    prova = rec_rand_create(lunghezza);
    printf("%s\n", prova[0].name);
    // rec_print(prova, lunghezza);
    rec_sort(prova, lunghezza);
    printf("dopo l'ordine \n");
    rec_print(prova, lunghezza);
    rec_free(prova, lunghezza);
}
