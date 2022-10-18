#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int value;
	struct node *next; /* pointer to the same structure */
} node;

typedef node *list;

/*
 * Assume that the list is in increasing order and insert the element
 * preserving the increasing order
 */
list list_insert_ordered(list p, int val);

/*
 * Concatenate two lists
 */
list list_cat(list before, list after);

/*
 * Insert elements at the head of the list
 */
list list_insert_head(list p, int val);

/*
 * Insert elements at the tail of the list
 */
list list_insert_tail(list p, int val);

/*
 * Print the list content
 */
void list_print(list p);

/*
 * Free the list
 */

void list_free(list p);

int provaa(int *numero)
{
	int *ciao = numero;
	ciao = 232;
	return *numero;
}

int main()
{
	list head = NULL;

	int a = 5;
	int b = a;
	printf("%i \n", b);

	/* insert some numbers in the list... */
	head = list_insert_tail(head, 2);
	head = list_insert_tail(head, 10);
	head = list_insert_tail(head, 15);
	head = list_insert_tail(head, 20);
	printf("%d \n", provaa(23));
	list_print(head);
	head = list_insert_ordered(head, 7);
	list_print(head);

	/* ... and clean everything up  */
	list_free(head);

	return 0;
}

list list_insert_ordered(list p, int val)
{
	list albero = NULL;
	for (; p != NULL; p = p->next)
	{
		if (p->next == NULL)
			break;
		albero = list_insert_tail(albero, p->value);
		if (p->value < val && p->next->value > val)
		{
			albero = list_insert_tail(albero, val);
		}
	}
	return albero;
}

list list_insert_tail(list p, int val)
{
	list new_el = malloc(sizeof(list));
	new_el->value = val;
	new_el->next = NULL;
	if (p == NULL)
	{
		p = new_el;
		return p;
	}

	list nodo = p;
	for (; nodo->next != NULL; nodo = nodo->next)
		;
	nodo->next = new_el;
	return p;
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
	if (p == NULL)
	{
		printf("Empty list\n");
		return;
	}
	printf("[%i]", p->value);
	for (; p->next != NULL; p = p->next)
	{
		printf(" -> [%i]", p->next->value);
	}
	printf("\n");
}

void list_free(list p)
{
	/* If p ==  NULL, nothing to deallocate */
	if (p == NULL)
	{
		return;
	}
	/* First deallocate (recursively) the next nodes... */
	list_free(p->next);
	/* ... then deallocate the node itself */
	free(p);
}
