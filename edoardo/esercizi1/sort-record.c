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
    record *ritorno = malloc(sizeof(*ritorno) * n);
    int i = 0;
    for (; i < n; i++)
    {
        int lunghezzaStringa = rand() % ((MAX_LEN + 1) + 1);
        char randomStringa[lunghezzaStringa];
        // Inzializzo la stringa
        int k = 0;
        for (; k < lunghezzaStringa - 1; k++)
        {
            char carattereBOH = (rand() % (90 - 65 + 1) + 65);
            randomStringa[k] = carattereBOH;
        }
        randomStringa[lunghezzaStringa - 1] = '\0';
        printf("%s\n", randomStringa);

        ritorno[i].age = rand() % (MAX_AGE - MIN_AGE + 1) + MIN_AGE;
        ritorno[i].name = randomStringa;
    }
    return ritorno;
}

void swap(record *prima, record *dopo)
{
    record temp = *prima;
    *prima = *dopo;
    *dopo = temp;
}

void rec_sort(record *v, int n)
{
    int i = 0;
    for (; i < n; i++)
    {
        int minIndx = 0;
        int k = 0;
        for (; k < n; k++)
        {
            if (v[k].age < v[minIndx].age)
            {
                minIndx = k;
            }
        }
        swap(&v[minIndx], &v[i]);
    }
}

void rec_print(record *v, int n)
{
    int i = 0;
    for (; i < n; i++)
    {
        printf("stringa casuale: %d, numero casuale: %d\n", v[i].name, v[i].age);
    }
}

int main()
{
    record *prova;
    int lunghezza = 5;
    prova = rec_rand_create(lunghezza);
    rec_print(prova, lunghezza);
    rec_sort(prova, lunghezza);
    // rec_print(prova, lunghezza);
}
