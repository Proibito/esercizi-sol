#include "list-module.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;
} node;

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
		{
			list next = head->next;
			return list_cut_below(head->next, cut_value);	
		}
	}
}

list list_dup(list head)
{
	if(head==NULL)
	{
		return NULL;
	}
	
	list newList = malloc(sizeof(*newList));
	newList->value = head->value;
	newList->next = list_dup(head->next);
	return newList;
	
}

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
}

list list_insert_ordered(list p, int val)
{
	node nuovo;
	nuovo.value = val;
	/*nuovo.next = NULL;*/

	list temp = p;
	while(temp->value <= nuovo.value)		/*Finchè il valore del nodo è minore o uguale al valore da inserire...*/
	{
		temp = temp->next;					/*...continuo a spostarmi nella lista.*/
	}

	if(temp->next == NULL)			/*Se sono al fondo della lista...*/
	{
		nuovo.next = NULL;			/*...*/
	}
	else							/*...oppure...*/
	{
		nuovo.next = temp->next->next;/*...*/
	}
	temp->next = &nuovo;	/*lego o inserisco il nodo nella lista*/
	
}

list list_cat(list before, list after)
{
	list before_backup = before;

	while(before->next != NULL)	/*Scorro la */
		before = before->next;

	before->next = after;

	return before_backup;
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

void list_free(list p)
{
	/* If p ==  NULL, nothing to deallocate */
	if(p == NULL) {
		return;
	}
	/* First deallocate (recursively) the next nodes... */
	list_free(p->next);
	/* ... then deallocate the node itself */
	free(p);			/*Ho dovuto commentare altrimenti mi dava un errore*/
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


