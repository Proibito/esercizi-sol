#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;   /* pointer to the same structure */
} node;

typedef node* list;

list list_delete_odd(list head);

list list_insert_ordered(list p, int val)
{
	node nuovo;
	nuovo.value = val;
	//nuovo.next = NULL;

	list temp = p;
	while(temp->value <= nuovo.value)		//Finchè il valore del nodo è minore o uguale al valore da inserire...
	{
		temp = temp->next;					//...continuo a spostarmi nella lista.
	}

	if(temp->next == NULL)			//Se sono al fondo della lista...
	{
		nuovo.next = NULL;			//...
	}
	else							//...oppure...
	{
		nuovo.next = temp->next->next;//...
	}
	temp->next = &nuovo;	//lego o inserisco il nodo nella lista
	
}

list list_cat(list before, list after)
{
	list before_backup = before;

	while(before->next != NULL)	//Scorro la 
		before = before->next;

	before->next = after;

	return before_backup;
}

list list_insert_head(list p, int val);

list list_insert_tail(list p, int val)
{
	 
	if(p->next != NULL)
	{
		list_insert_tail(p->next, val);
	}
	else
	{
		list list_end = malloc(sizeof(*list_end));
		list_end->value = val;
		p->next = list_end;
	}

	return p;
}

void list_print(list p);

void list_free(list p);

list list_delete_if(list head, int to_delete)
{
	printf("Elimino elemento %d\n", to_delete);
	if(head == NULL)
	{
		return NULL;
	}
	else
	{
		if(head->value != to_delete)
		{
			list newNode;
			newNode = malloc(sizeof(*newNode));
			newNode->value = head->value;
			newNode->next = list_delete_if(head->next, to_delete);
			return newNode;
		}
		else
		{
			list next = head->next;
			free(head);
			return next;
		}
	}


	//VERSIONE NON RICORSIVA CHE HA DEI PROBLEMI
	/*list head_backup = head;
	while(head->next!=NULL)			//PROBLEMA IN QUESTO BLOCCO
	{									//non riesco a trovare la condizione corretta per la rimozione del valore finale della lista
		if(head->value==to_delete)
		{
			*head = *head->next;
			
			//free()
			return head_backup;
		}
		head = head->next;
	}

	return head_backup;*/
}

list list_cut_below(list head, int cut_value);

list list_dup(list head);

int main()
{
	int limit = 12;		//Modificabile
	node* old_pointer, *new_pointer;
	list head = NULL;

	/* insert some numbers in the list... */
	head = list_insert_head(head, 10);
	head = list_insert_head(head, 2);
	head = list_insert_head(head, 15);
	/* ... print them... */
	list_print(head);

	head = list_delete_if(head, 15);		//Rimuovi
	head = list_delete_if(head, 2);		//Rimuovi
	list_print(head);					//Stampa

	printf("\nRESET\nRimozione elementi in posizione dispari\n");
	head = NULL;
	head = list_insert_head(head, 24);
	head = list_insert_head(head, 10);
	head = list_insert_head(head, 2);
	head = list_insert_head(head, 15);
	head = list_insert_head(head, 18);
	list_print(head);
	head=list_delete_odd(head);
	list_print(head);

	printf("\nRESET\nRimozione elementi di valore inferiore al valore %d\n", limit);
	head = NULL;
	head = list_insert_head(head, 24);
	head = list_insert_head(head, 10);
	head = list_insert_head(head, 2);
	head = list_insert_head(head, 15);
	head = list_insert_head(head, 18);
	list_print(head);
	head=list_cut_below(head, limit);
	list_print(head);

	printf("\nRESET\nDuplicazione lista\n");
	head = NULL;
	head = list_insert_head(head, 24);
	head = list_insert_head(head, 10);
	head = list_insert_head(head, 2);
	head = list_insert_head(head, 15);
	head = list_insert_head(head, 18);
	list_print(head);
	old_pointer = (head);
	head = list_dup(head);
	new_pointer  = (head);
	list_print(head);
	printf("\nVerifica duplicazione: ");
	if(old_pointer != new_pointer)
	{
		printf(" CORRETTO\n");
	}
	else
	{
		printf(" NON CORRETTO\n");
	}


	/* ... and clean everything up  */
	list_free(head);

	return 0;
}

list list_insert_head(list p, int val)
{
	list new_el;

	/* Allocate the new node */
	new_el = malloc(sizeof(*new_el));
	/* Setting the data */
	new_el->value = val;
	/* head insertion: old head becomes .next field of new head */
	new_el->next = p;
	/* new head is the pointer to the new node */
	return new_el;
}

void list_print(list p)
{
	/* Looping all nodes until p == NULL */
	if (p == NULL) {
		printf("Empty list\n");
		return;
	}
	printf("[%i]", p->value);
	for(; p->next!=NULL; p = p->next) {
		printf(" -> [%i]", p->next->value);
	}
	printf("\n");
}

void list_free(list p)
{
	/* If p ==  NULL, nothing to deallocate */
	if(p == NULL) {
		return;
	}
	/* First deallocate (recursively) the next nodes... */
	list_free(p->next);
	/* ... then deallocate the node itself */
	free(p);			//Ho dovuto commentare altrimenti mi dava un errore
}

/*list list_delete_if(list head, int to_delete)
{
	list head_backup = head;

	while(head->value!=to_delete)
	{
		if(head->next==NULL)
		{
			printf("Valore non trovato\n");
			return NULL;
		}
		else
		{
			head = head->next;
		}
	}
	head->next = head->next->next;
}*/

list list_delete_odd(list head)
{
	list newList;
	if(head != NULL)
	{
		head = head->next;
		if(head != NULL)
		{
			newList = malloc(sizeof(*newList));
			newList->value = head->value;
			head = head->next;
			newList->next = list_delete_odd(head);
			return newList;
		}
	}
	else
	{
		return NULL;
	}
}

list list_cut_below(list head, int cut_value)
{
	if(head == NULL)
	{
		return NULL;
	}
	else
	{
		if(head->value >= cut_value)
		{
			list newNode;
			newNode = malloc(sizeof(*newNode));
			newNode->value = head->value;
			newNode->next = list_cut_below(head->next, cut_value);
			return newNode;
		}
		else
		{			//DA RISOLVERE... C'è un problema
			list next = head->next;
			return list_cut_below(head->next, cut_value);
			
			}
	}
}

list list_dup(list head)
{
	/*list newList;
	newList = malloc(sizeof(*newList));
	//newList->next = NULL;
	while (head!=NULL)
	{
		newList = list_insert_tail(newList, head->value);
		head = head->next;
	}
	
	printf("Risultato duplicazione:\n");
	list_print(newList);
	return newList;*/

	if(head==NULL)
	{
		return NULL;
	}
	
	list newList = malloc(sizeof(*newList));
	newList->value = head->value;
	newList->next = list_dup(head->next);
	return newList;
	
}
