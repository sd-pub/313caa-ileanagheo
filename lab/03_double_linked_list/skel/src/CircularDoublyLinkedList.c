/*Gheorghisor Ileana-Teodora, 313CA*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
	doubly_linked_list_t *list;

    list = malloc(sizeof(doubly_linked_list_t));
    list->head = NULL;
    list->data_size = data_size;
    list->size = 0;

    return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	unsigned int i;
	 dll_node_t* curr;
	/* Daca n < 0, afisez eroare. */
    if (n < 0) {
    	printf("%s\n", "Eroare.");
    	return NULL;
    }
    /* Daca lista e goala, returnez NULL. */
    if (list == NULL || list->head == NULL) {
    	return NULL;
    }
    /* Daca n >= nr_noduri, iau restul impartirii lui n la nr_noduri pentru a
    afla pozitia nodului in lista. */
    if (n >= list->size) {
    	n %= list->size;
    }

    curr = list->head;

    for (i = 0; i < n; i++) {
    	curr = curr->next;
    }

    return curr;  
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    dll_node_t *new;

    if (n < 0 || list == NULL) {
    	return;
    }

    new = malloc(sizeof(dll_node_t));
    new->data = malloc(sizeof(list->data_size));
    memcpy(new->data, data, sizeof(list->data_size));

    /* Daca lista e goala, adaug head. */
    if (list->size == 0) {
        list->head = new;
        new->prev = list->head;
        new->next = list->head;
        list->size++;

    } else if (n == 0) {
    	/* Cand n = 0, inlocuiesc head-ul. */
    	new->prev = list->head->prev;
    	new->next = list->head;
        list->head->prev->next = new;
        list->head->prev = new;
        list->head = new;
        list->size++;

    } else if (n >= list->size) {
    	/* Daca n >= nr_noduri, adaug la final. */
    	new->prev = list->head->prev;
    	new->next = list->head;
    	list->head->prev->next = new;
    	list->head->prev = new;
    	list->size++;

    } else {
    	/* Altfel, adaug nod direct pe pozitia ceruta. */
   		dll_node_t *node1, *node2;
   		node1 = dll_get_nth_node(list, n - 1);
    	node2 = dll_get_nth_node(list, n);

    	new->prev = node1;
    	new->next = node2;
    	node1->next = new;
    	node2->prev = new;
    	list->size++;
	}
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	/* Daca n < 0, afisez eroare. */
	if (n < 0) {
		printf("%s\n", "Eroare.");
		return NULL;
	}
	else {
		struct dll_node_t *curr, *prevv, *nextt;

		if (list == NULL || list->head == NULL) {
			return NULL;
		}
		
		/* Daca n >= nr_noduri - 1, sterg ultimul nod. */
		if (n >= list->size - 1) {
			if(list->size == 1) {
				list->size--;
				free(list->head->data);
				free(list->head);
				return(list->head);
			} else {
				curr = list->head->prev; /* Ultimul nod */
				prevv = list->head->prev->prev; /* Penultimul */
				nextt = list->head; /* Primul aka head */
				prevv->next = nextt;
				nextt->prev = prevv;
				list->size--;
				free(curr->data);
				free(curr);
				return curr;
			}

		} else {
			/* Altfel, sterg nodul de pe pozitia n. */
			curr = dll_get_nth_node(list, n);
			prevv = curr->prev;
			nextt = curr->next;
			prevv->next = nextt;
			nextt->prev = prevv;
			if (n == 0) {
				list->head = nextt;
			}
			list->size--;
			free(curr->data);
			free(curr);
			return curr;
		}
	}
	return NULL;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    if (*pp_list == NULL || pp_list == NULL) {
    	return;
    }
    while (dll_get_size(*pp_list) > 0) {
    	dll_remove_nth_node(*pp_list, 1);
    }
    free(*pp_list);
    *pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
	unsigned int i;
	dll_node_t* curr;

    if (list == NULL || list->size == 0) {
    	return;
    }

    curr = list->head;

    for (i = 0; i < list->size; i++) {
    	printf("%d ", *((int *)curr->data));
    	curr = curr->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
	unsigned int i;
	dll_node_t* curr;

    if (list == NULL || list->size == 0) {
    	return;
    }

    curr = list->head;

    for (i = 0; i < list->size; i++) {
    	printf("%s ", (char*)curr->data);
    	curr = curr->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_left_circular(doubly_linked_list_t* list, dll_node_t* start)
{
	unsigned int i;
	dll_node_t* curr;

	if (list == NULL || list->size == 0) {
    	return;
    }
    
    curr = start;

    for (i = 0; i < list->size; i++) {
    	printf("%d ", *((int *)curr->data));
    	curr = curr->prev;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_right_circular(doubly_linked_list_t* list, dll_node_t* start)
{
	unsigned int i;
	dll_node_t* curr;

    if (list == NULL || list->size == 0) {
    	return;
    }
    
    curr = start;

    for (i = 0; i < list->size; i++) {
    	printf("%d ", *((int *)curr->data));
    	curr = curr->next;
    }
    
    printf("\n");
}

doubly_linked_list_t*
Ex313CAa (doubly_linked_list_t* list1, doubly_linked_list_t* list2)
{
	unsigned int i = 0, n, j = 0, k = 0;
    dll_node_t *curr1, *curr2;
    doubly_linked_list_t *l;
    l = dll_create(sizeof(int));
    curr1 = list1->head;
    curr2 = list2->head;
    n = dll_get_size(list1) + dll_get_size(list2);
    while (i < n) {
        if (j < list1->size && k < list2->size) {
            if (*((int *)curr1->data) <= *((int *)curr2->data)) {
                dll_add_nth_node(l, i, curr1->data);
                curr1 = curr1->next;
                j++;
                i++;
            } else {
                dll_add_nth_node(l, i, curr2->data);
                curr2 = curr2->next;
                k++;
                i++;
            }
        }
        if (j == list1->size && k < list2->size) {
            while (k < list2->size) {
                dll_add_nth_node(l, i, curr2->data);
                curr2 = curr2->next;
                k++;
                i++;
            }
        }
        if (j < list1->size && k == list2->size) {
            while (j < list1->size) {
                dll_add_nth_node(l, i, curr1->data);
                curr1 = curr1->next;
                j++;
                i++;
            }
        }
    }

	return l;
}

doubly_linked_list_t*
Ex312CAb (doubly_linked_list_t* A, doubly_linked_list_t* B)
{
	unsigned int i = 0;
	int suma = 0;
    dll_node_t *curr1, *curr2;
    doubly_linked_list_t *C;
    C = dll_create(sizeof(int));
    curr1 = A->head;
    curr2 = B->head;

    if (dll_get_size(A) > dll_get_size(B)) {
    	while (i < B->size) {
    		suma = *((int *)curr1->data) + *((int *)curr2->data);
    		curr1 = curr1->next;
    		curr2 = curr2->next;
    		dll_add_nth_node(C, i, suma);
    		i++;
    	}
    	while (i < A->size) {
    		dll_add_nth_node(C, i, curr1->data);
    		curr1 = curr1->next;
    		i++;
    	}

    } else {
		while (i < A->size) {
    		suma = *((int *)curr1->data) + *((int *)curr2->data);
    		curr1 = curr1->next;
    		curr2 = curr2->next;
    		dll_add_nth_node(C, i, suma);
    		i++;
    	}
    	while (i < B->size) {
    		dll_add_nth_node(C, i, curr2->data);
    		curr2 = curr2->next;
    		i++;
    	}
    }
	return C;
}
