#include "treap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRIORITY 1000

// Creeaza structura Treap-ului
Treap_tree*
treap_create(int (*cmp)(void*, void*))
{
    srand(time(NULL));
    Treap_tree* tree = malloc(sizeof(Treap_tree));
    tree->compar = cmp;
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    return tree;
}
void
node_free(Node** node)
{

    if (!(*node)) {
        return;
    }
    node_free(&(*node)->left);
    node_free(&(*node)->right);

    free((*node)->data);
    free(*node);
}

void
treap_free(Treap_tree* tree)
{
    if (tree->root != NULL) {
        node_free(&tree->root);
    }
    free(tree);
}
/* Creeaza un nod
 * @param1: Valoarea ce trebuie pusa in nod.
 * @param2: Numarul de octeti pe care scrie valoarea.
 */
Node*
node_create(void* value, int data_size)
{
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = malloc(data_size);

    // Copiere octet cu octet din value, in nodul curent.
    for (int i = 0; i < data_size; ++i) {
        *(char*)(node->data + i) = *(char*)(value + i);
    }

    // Nodurile frunze au inaltimea 0.
    node->priority = rand() % MAX_PRIORITY;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int
max(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}
// Nodurile NULL au prioritatea -1 pentru a pastra proprietatea de max-heap.
int
priority(Node* node)
{
    if (node == NULL) {
        return -1;
    }
    return node->priority;
}
/* Rotire dreapta
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *      node  			    lson
 *     /    \			   /    \
 *   lson    y    --->    x    node
 *   /  \     		           /   \
 *  x   lrson                lrson  y
 */
void
rotate_right(Node** node)
{
    // TODO: Completati rotire dreapta
    Node *left, *right_left;
	left = (*node)->left;
	right_left = left->right;
	left->right = (*node);
	(*node)->left = right_left;
	(*node) = left;
}
/* Rotire stanga
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *     node  			    rson
 *    /    \			   /    \
 *   x     rson    --->  node    y
 *         /   \		 /   \
 *       rlson  y       x   rlson
 */
void
rotate_left(Node** node)
{
    // TODO: Completati rotire stanga.
    Node *right, *left_right;
	right = (*node)->right;
	left_right = right->left;
	right->left = *node;
	(*node)->right = left_right;
	(*node) = right;
}
/* Inserare in Treap
 *
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in Treap.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din Treap.
 */
void
treap_insert(Node** node,
             void* value,
             int data_size,
             int (*compar)(void*, void*))
{
    // TODO: Inserati recursiv in arbore
    if ((*node) == NULL) {
		(*node) = node_create(value, data_size);
		return ;
	}

	int rc;
	rc = compar(value, (*node)->data);

    // TODO: Reechilibrare arbore

    if (rc < 0) {
		treap_insert(&(*node)->left, value, data_size, compar);
		if (priority((*node)->left) > priority((*node))) {
			rotate_right(node);
		}

	} else {
		treap_insert(&(*node)->right, value, data_size, compar);
		if (priority((*node)->right) > priority((*node)))
			rotate_left(node);
	}
}

/* Stergere din Treap
 *
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in Treap.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din Treap.
 */
void
treap_delete(Node** node,
             void* value,
             int data_size,
             int (*compar)(void*, void*))
{
    // TODO: Stergeti recursiv din arbore
    if(*node == NULL) {
    	return;
    }

	int rc;
	rc = compar(value, (*node)->data);

	if (rc < 0) {
		treap_delete(&(*node)->left, value, data_size, compar);

	} else if (rc > 0) {
		treap_delete(&(*node)->right, value, data_size, compar);

	} else if ((*node)->left == NULL && (*node)->right == NULL) { 
			//Daca e frunza, il sterg direct.
			free((*node)->data);
			free(*node);
			*node = NULL;

	} else if (priority((*node)->left) > priority((*node)->right)) {
			//Dar daca nu, trebuie sa fac rotate-urile
			rotate_right(node);
			treap_delete(node, value, data_size, compar);
	} else {
			rotate_left(node);
			treap_delete(node, value, data_size, compar);
	}
}
void*
get_key(Node* node, void* value, int data_size, int (*compar)(void*, void*))
{
    // TODO: Cautarea unei valori in arbore
	if (node == NULL || node->data == NULL) {
		return NULL;
	}

    int rc;
    rc = compar(value, node->data);

    if (rc == 0) {
    	return value;
    } else {
    	if (rc < 0) {
    		return get_key(node->left, value, data_size, compar);
    	} else {
    		return get_key(node->right, value, data_size, compar);
    	}	
	}
}

/* Verifica daca un arbore respecta proprietatile unui treap
 *
 * @param1: Nodul curent in parcurgerea recursiva.
 * @param2: Functia de comparare a datelor din fiecare nod.
 * @return: Daca arborele e Treap, vom returna numarul de noduri al arborelui,
 * 			altfel, vom returna o valoare negativa.
 */
int
check_treap(Node* node, int (*compar)(void*, void*))
{
    if (node == NULL) {
        return 0;
    } else if (node->left == NULL && node->right == NULL) {
        return 1;
    } else if (node->left == NULL) {
        if (priority(node) >= priority(node->right) &&
            compar(node->data, node->right->data) <= 0) {
            return 1 + check_treap(node->right, compar);
        }
        return INT_MIN;
    } else if (node->right == NULL) {
        if (priority(node) >= priority(node->left) &&
            compar(node->data, node->left->data) >= 0) {
            return 1 + check_treap(node->left, compar);
        }
        printf("%d %d %d\n",
               priority(node),
               priority(node->left),
               priority(node->right));
        return INT_MIN;
    } else {
        if (priority(node) >= priority(node->left) &&
            priority(node) >= priority(node->right) &&
            compar(node->data, node->left->data) >= 0 &&
            compar(node->data, node->right->data) <= 0) {
            return 1 + check_treap(node->left, compar) +
                   check_treap(node->right, compar);
        }
        printf("%d %d %d\n",
               priority(node),
               priority(node->left),
               priority(node->right));
        return INT_MIN;
    }
}
