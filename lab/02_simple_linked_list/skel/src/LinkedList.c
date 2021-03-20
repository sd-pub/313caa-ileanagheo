/* Gheorghisor Ileana-Teodora, 313CA */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"


linked_list_t* ll_create(unsigned int data_size)
{
	struct linked_list_t *list;

    list = malloc(sizeof(linked_list_t));
    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;

    return list;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
	/* Daca n < 0, afisez eroare. */
	if (n < 0) {
		printf("%s\n", "Eroare.\n");
	}
	else {
		struct ll_node_t *new, *curr, *nextt;

		if (list == NULL) {
			return;
		}
		new = (struct ll_node_t*)malloc(sizeof(struct ll_node_t));
		new->data = (void*)malloc(sizeof(void*));

		/* Daca n >= nr_noduri, adaug la final. */
	    if (n >= list->size && list->size != 0) {
	    	memcpy(new->data, new_data, sizeof(void*));
			new->next = NULL;
			curr = list->head;
			while (curr->next != NULL) {
				curr = curr->next;
			}
			curr->next = new;
			list->size++;

		} else if (n > 0 && list->size != 0) {
			/* Altfel, inserez nodul intre curr si nextt, pe pozitia n. */
			unsigned int i = 0;
			curr = list->head;
			while (curr->next != NULL && i < n) {
				curr = curr->next;
				i++;
			}
			memcpy(new->data, new_data, sizeof(void*));
			nextt = curr->next;
			curr->next = new;
			new->next = nextt;
			list->size++;

		} else if (n == 0 || list->size == 0) {
			/* Pentru primul nod, n = 0. */
			memcpy(new->data, new_data, sizeof(void*));
			new->next = list->head;
			list->head = new;
			list->size++;
		}
	}
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t* ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    /* Daca n < 0, afisez eroare. */
	if (n < 0) {
		printf("%s\n", "Eroare.\n");
		return NULL;
	}
	else {
		struct ll_node_t *last, *prev, *curr, *first;

		if (list == NULL || list->head == NULL) {
			return NULL;
		}
		
		/* Daca n >= nr_noduri - 1, sterg ultimul nod. */
		if (n >= list->size - 1) {
			if(list->size == 1) {
				list->size--;
				return(list->head);
			}
			last = list->head->next;
			prev = list->head;
			while (last->next != NULL) {
				prev = last;
				last = last->next;
			}
			prev->next = NULL;
			list->size--;
			return last;

		} else if (n != 0) {
			/* Altfel, sterg nodul de pe pozitia n (cu exceptia n = 0). */
			unsigned int i = 1;
			prev = list->head;
			curr = list->head->next;
			while (curr->next != NULL && i < n) {
				prev = curr;
				curr = curr->next;
				i++;
			}
			prev->next = curr->next;
			list->size--;
			return curr;

		} else if (n == 0) {
			/* Sterg primul nod pt n = 0. */
			first = list->head;
			list->head = first->next;
			list->size--;
			return first;
		}
	}
	return NULL;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int ll_get_size(linked_list_t* list)
{
    return (unsigned int)list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void ll_free(linked_list_t** pp_list)
{
    if (*pp_list == NULL || pp_list == NULL) {
    	return;
    }
    while (ll_get_size(*pp_list) > 0) {
    	free(ll_remove_nth_node(*pp_list, 0));
    }
    free(*pp_list);
    *pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void ll_print_int(linked_list_t* list)
{
    struct ll_node_t *curr;

    if (list == NULL) {
    	return;
    }
    curr = list->head;
    while (curr != NULL) {
    	printf("%u ", *((unsigned int*)curr->data));
    	curr = curr->next;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void ll_print_string(linked_list_t* list)
{
    struct ll_node_t *curr;

    if (list == NULL) {
    	return;
    }
    curr = list->head;
    while (curr != NULL) {
    	printf("%s ", (char*)curr->data);
    	curr = curr->next;
    }
    printf("\n");
}

/* Functia de la exercitiul 2*/
void ll_ex2(linked_list_t* list)
{
	unsigned int i = 0;
	struct linked_list_t *indici_pari, *indici_impari;
	struct ll_node_t *curr;

	indici_pari = ll_create(sizeof(int));
	indici_impari = ll_create(sizeof(int));
	curr = list->head;

	while (curr != NULL) {
		ll_add_nth_node(indici_pari, i, curr->data);
		curr = curr->next;
		i++;
		if (curr != NULL) {
			ll_add_nth_node(indici_impari, i, curr->data);
			curr = curr->next;
			i++;
		}
	}
	ll_print_int(indici_pari);
	ll_print_int(indici_impari);
}
