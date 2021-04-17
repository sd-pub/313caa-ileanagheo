/* Gheorghisor Ileana-Teodora, 313CA */
#include <stdio.h>
#include <stdlib.h>

#include "MatrixGraph.h"

/**
 * Initializeaza graful cu numarul de noduri primit ca parametru si aloca
 * memorie pentru matricea de adiacenta a grafului.
 */
matrix_graph_t*
mg_create(int nodes)
{
	/* TODO */
	matrix_graph_t *graph = calloc(1, sizeof(matrix_graph_t));
	DIE(!graph, "Graph calloc failed!\n");
	graph->matrix = (int**)calloc(nodes, sizeof(int*));
	DIE(!graph->matrix, "Graph matrix calloc failed!\n");
	for (int i = 0; i < nodes; i++) {
		graph->matrix[i] = (int*)calloc(nodes, sizeof(int));
		DIE(!graph->matrix[i], "Graph matrix calloc failed!\n");
	}
	graph->nodes = nodes;
	return graph;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void
mg_add_edge(matrix_graph_t* graph, int src, int dest)
{
	/* TODO */
	if (!graph->matrix) {
		printf("No matrix!\n");
		return;
	}
	graph->matrix[src][dest] = 1;
	graph->matrix[dest][src] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int
mg_has_edge(matrix_graph_t* graph, int src, int dest)
{
	/* TODO */
	if (!graph->matrix) {
		printf("No matrix!\n");
		return 0;
	}
	return graph->matrix[src][dest];
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void
mg_remove_edge(matrix_graph_t* graph, int src, int dest)
{
	/* TODO */
	if (!graph->matrix) {
		printf("No matrix!\n");
		return;
	}
	graph->matrix[src][dest] = 0;
	graph->matrix[dest][src] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void
mg_free(matrix_graph_t* graph)
{
	/* TODO */
	if (!graph || !graph->matrix) {
		printf("No graph or no matrix!\n");
		return;
	}
	for (int i = 0; i < graph->nodes; i++) {
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph);
}
