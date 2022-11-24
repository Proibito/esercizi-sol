#include <stdio.h>

typedef struct node {
	int value;
	struct node * next;
} node;

typedef node* list;

list list_delete_if(list head, int to_delete);
list list_delete_odd(list head);
list list_cut_below(list head, int cut_value);
list list_dup(list head);

int main()
{
    
}

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
