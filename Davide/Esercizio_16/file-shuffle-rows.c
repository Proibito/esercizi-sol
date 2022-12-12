#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Sample per fgets
	fgets(stringa, sizeof(stringa), stdin);
*/

typedef struct element
{
	char string[100];
	struct element* next;
}element;

typedef element * list;
element* list_seek(list head, int position);
void erase_element(list head, int position);

int list_element_counter(list head);

int main(int argc, char* argv[])
{
	FILE *fp_1, *fp_2;
	list head, head_backup;
	int list_length, pick;
	element *temp_element;
	srand(time(0));

	if(fp_1 = fopen(argv[1], "r")==NULL)
	{
		fprintf(stderr, "Errore di apertura del file di nome: %s\n", argv[1]);
	}
	if(fp_2 = fopen(argv[2], "w"))
	{
		fprintf(stderr, "Errore di apertura del file di nome: %s\n", argv[2]);
	}
	head = NULL;

	/* RICEZIONE */
	/* Salvataggio all'interno di una lista. */
	head = malloc(sizeof(*head));
	head_backup = head;
	while(fgets(head->string, sizeof(head->string), fp_1) != NULL)
	{
		printf("Stringa head->string: %s", head->string);
		head->next = malloc(sizeof(*head));
		head->next->next = NULL;        /* Forse superfluo */
		head = head->next;
	}

	printf("Fine del file raggiunta.\n");
	head = head_backup;

	/* LOOP DI COPIATURA */
	/* Con un loop fino allo svuotamento della lista scegliamo un elemento della lista e lo stampiamo nel file. */
	if(head == NULL)
	{
		printf("\nIl file non conteneva stringhe.\nNessuna stringa è stata copiata nel secondo file.");
		return -1;    
	} 
	while(head!=NULL) 
	{
		list_length = list_element_counter(head); 
		if(list_length <= 0) break;
		pick = rand()%(list_length);
		head = list_seek(head, pick);
		fputs(head->string, fp_2);

/*      ELIMINAZIONE ELEMENTO DELLA LISTA       */
		if(head == head_backup)     /*Se siamo al primo elemento della lista...*/
		{
			temp_element = head_backup;
			head_backup = head_backup->next;
			//free(temp_element->string);
			free(temp_element);
		}
		else                        /*... oppure se non siamo al primo elemento...*/
		{
			temp_element = head_backup;
			while (temp_element -> next != head)
			{
				temp_element = temp_element->next;
			}
			temp_element->next = temp_element->next->next;
		}


		head = head_backup;
	}
	printf("\nCopia stringhe completata.\n");

	fflush(NULL);

	fclose(fp_1);
	fclose(fp_2);

	return 0;
}

element* list_seek(list head, int position)
{
	int i;
	for(i=0;i<position;i++)
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
		head = head->next;
	}
	return counter-1;
}

void erase_element(list head, int position)
{
	element * temp;
	temp = list_seek(head, position);

	temp = list_seek(head, position)->next;

	free(temp);
}
