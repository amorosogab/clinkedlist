#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

void *int_copy(void *obj);
void print_list(linkedlist_t list);

int main(void)
{
	int cmd, no_exit = 1;
	linkedlist_t list = NULL;

	do
	{
		printf("1. Inserisci elemento\n"
			   "2. Estrai testa\n"
			   "3. Stampa lista\n"
			   "4. Cancella nodo\n"
			   "5. Cancella oggetto\n"
			   "6. Exit\n"
			   "Inserisci comando: ");
		scanf("%d", &cmd);

		switch(cmd)
		{
			case 1:
			{
				int elem;

				printf("Inserisci intero: ");
				scanf("%d", &elem);
				list = ll_insert_copy(list, &elem, int_copy);
			}
			break;

			case 2: list = ll_extract_head_destroy(list, free);
			break;

			case 3: print_list(list);
			break;

			case 4:
			{
				int n;

				printf("Inserisci il numero (in ordine di visualizzazione) del nodo da cancellare: ");
				scanf("%d", &n);

				int i;
				struct node_list *head;
				for(head = list, i = 1; list && i < n; list = list->next, i++)
					;

				struct node_list *nl = list;
				list = head;
				free(nl->object);
				list = ll_delete_node_list(list, nl);
			}
			break;

			case 5:
			{
				int n;

				printf("Inserisci il numero intero da cancellare: ");
				scanf("%d", &n);

				struct node_list *head;
				for(head = list; list && *((int *) list->object) != n; list = list->next)
					;

				void *obj = list->object;
				list = head;
				list = ll_delete_node_object(list, obj);
				free(obj);

			}
			break;

			case 6: no_exit = 0;
			break;

			default: no_exit = 0;
		}

		printf("\n");
	}while(no_exit);

	ll_destroy(list, free);

	return 0;
}

void *int_copy(void *obj)
{
	int *cpy = (int *) malloc(sizeof(int));
	if(cpy)
		*cpy = obj != NULL ? *((int *) obj) : 0;

	return cpy;
}

void print_list(linkedlist_t list)
{
	while(list)
	{
		if(list->object)
			printf("[%d] ", *((int *) list->object));
		else
			printf("[NULL] ");

		list = list->next;
	}

	printf("\n");
}