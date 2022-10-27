#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;   /* pointer to the same structure */
} node;

typedef node* list;

/*
 * Assume that the list is in increasing order and insert the element
 * preserving the increasing order
 */
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

/*
 * Concatenate two lists
 */
list list_cat(list before, list after)
{
	list before_backup = before;

	while(before->next != NULL)	//Scorro la 
		before = before->next;

	before->next = after;

	return before_backup;
}

/*
 * Insert elements at the head of the list
 */
list list_insert_head(list p, int val);
/*{
	node nuovo;
	nuovo.value = val;
	nuovo.next = p;
	return &nuovo;
}*/

/*
 * Insert elements at the tail of the list
 */
list list_insert_tail(list p, int val)
{
	node nuovo;
	list p_backup = p;
	nuovo.value = val;
	nuovo.next = NULL;
	for(;p->next != NULL;p = p->next)
	{}

	p->next = &nuovo;

	return p;
}

/*
 * Print the list content
 */
void list_print(list p);
/*{
	printf("Stampa della lista:\n");
	if(p==NULL)
	{
		printf("La lista è vuota.\n");
		return;
	}
	else
	{
		printf("%d\n", p->value);
	}

	while(p->next != NULL)
	{
		printf("%d\n", p->value);
		p = p->next;
	}

	printf("%d\n", p->value);

	return;		//inutile ma mi sembrava ordinato metterlo
}*/

/*
 * Free the list
 */

void list_free(list p);
/*{
	free(p);
}*/

list list_delete_if(list head, int to_delete)
{
	list head_backup = head, head_backup_2;
	int contagiri=0, i;
	while(head->next!=NULL)
	{
		contagiri++;
		if(head->value==to_delete)
		{
			head_backup_2=head;
			head = head_backup;
			for(i=0;i<contagiri;i++)
			{
				head=head->next;
			}
		}
	}
}

int main()
{
	list head = NULL;

	/* insert some numbers in the list... */
	head = list_insert_head(head, 10);
	head = list_insert_head(head, 2);
	head = list_insert_head(head, 15);
	/* ... print them... */
	list_print(head);
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
	free(p);
}

list list_delete_if(list head, int to_delete)
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
}