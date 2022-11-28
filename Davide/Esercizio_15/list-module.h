#ifndef MODULE_LIST_1
#define MODULE_LIST_1

/* Dichiarazione tipo list */
typedef struct node* list;

/*  Dichiarazione delle funzioni utilizzate nel file test-list-module.
    Corpo delle funzioni presente in list-module.c */
list list_delete_if(list head, int to_delete);
list list_delete_odd(list head);
list list_cut_below(list head, int cut_value);
list list_dup(list head);
list list_insert_ordered(list p, int val);
list list_cat(list before, list after);
list list_insert_head(list p, int val);
list list_insert_tail(list p, int val);
void list_free(list p);
void list_print(list p);

#endif