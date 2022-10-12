#include <stdio.h>
#include <stdlib.h>
#define MIN_AGE 5
#define MAX_AGE 7

typedef struct
{
    char *name;
    int age;
} record;

record *rec_rand_create(int n)
{
    record *ritorno = malloc(sizeof(record));
    int i = 0;
    for (; i < n; i++)
    {
        ritorno[i].age = rand() % (MIN_AGE - 1);
        ritorno[i].name = 
        printf("%d\n", ritorno[i].age);
    }
}

int main()
{
    rec_rand_create(4);
}
