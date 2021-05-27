/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <resume_or_paste_the_task_here>
 */
#include <stdio.h>
#include <math.h>

#include "binary_tree.h"

void nivel(b_node_t *current, unsigned int *parents, unsigned int N)
{
	if (current == NULL) //Daca nu mai exista copii
		return;
	if (*parents == N) { //Daca am ajuns la nivelul cerut
		printf("%d\n", *(int*)current->data);
		return;
	}
	//Cresc o singura data nr de parinti pt ambele apelari ale functiei nivel.
	*parents += 1;
	nivel(current->left, parents, N);
	nivel(current->right, parents, N);
}

int main(void)
{
    /* TODO */

    //Ex 313CAa)
    //Am reusit sa verific cu 3 noduri si merge. (insert-ul merge cu 3 noduri)
    unsigned int N;
    scanf("%d", &N);

    //Crearea copacului cu elemente de la 1 la 3;
    b_tree_t *tree = b_tree_create(sizeof(int));
    for (unsigned int i = 1; i <= 3; i++) {
    	b_tree_insert(tree, &i);
    }

    //Cautarea copiilor de pe nivelul N.
    //Consider root-ul pe nivelul 0.
    /*
     * Desi nu este foarte eficient, ma gandeam sa parcurg tot arborele si
     * sa numar parintii parintilor pentru fiecare copil. Cand numarul = N,
     * afisez copilul.
     */
    unsigned int parents;
    parents = 0;

    nivel(tree->root, &parents, N);

    return 0;
    exit(EXIT_FAILURE);
}
