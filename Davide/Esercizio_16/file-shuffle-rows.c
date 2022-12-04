#include <stdio.h>
#include <stdlib.h>

/*
    Sample per fgets
    fgets(stringa, sizeof(stringa), stdin);
*/

typedef struct element
{
    char* string;
    struct element* next;
}element;

typedef element * list;

element* seek(list head, int position);

int list_element_counter(list head);

int main(int argc, char* argv[])
{
    FILE * fp_1;
    FILE * fp_2;
    list head, head_backup;
    int list_length;
    srand(time(0));

    fp_1 = fopen(argv[1], "r");
    fp_2 = fopen(argv[2], "w");
    head = NULL;

    /* RICEZIONE */
    /* Salvataggio all'interno di una lista. */
    head = malloc(sizeof(element));
    head_backup = head;
    printf("Stringa head->string \"%s\"\n", head->string);
    while(fscanf(fp_1, "%s", head->string) >0)
    {
        printf("Stringa head->string \"%s\"", head->string);
        head->next = malloc(sizeof(element));
        head->next->next = NULL;        /* Forse superfluo */
        head = head->next;
    }
    printf("\nFine del file raggiunta.");
    head = head_backup;

    /* LOOP DI COPIATURA */
    /* Con un loop fino allo svuotamento della lista scegliamo un elemento della lista e lo stampiamo nel file. */
    if(head == NULL)
    {
        printf("\nIl file non conteneva stringhe.\nNessuna stringa è stata copiata nel secondo file.");
    }
    while(head!=NULL)
    {
        list_length = list_element_counter(head);
        fprintf(fp_2, seek(head, rand()%list_length)->string);
    }
    printf("\nCopia stringhe completata.");
    
    fclose(fp_1);
    fclose(fp_2);

    return 0;
}

element* seek(list head, int position)
{
    int i;
    for(i=0;i<=position;i++)
    {
        head = head->next;
    }
    return head;
}

int list_element_counter(list head)
{
    int counter;
    counter = 0;
    while(head!=NULL)
    {
        counter++;
    }
    return counter;
}

