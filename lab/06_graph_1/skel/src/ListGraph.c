#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "utils.h"

list_graph_t*
lg_create(int nodes)
{
	/* TODO */
	list_graph_t *graph = calloc(1, sizeof(list_graph_t));
	DIE(!graph, "Graph calloc failed!\n");
	graph->neighbors = (linked_list_t**)calloc(nodes, sizeof(linked_list_t*));
	DIE(!graph->neighbors, "Neighbors calloc failed!\n");
	for (int i = 0; i < nodes; i++) {
		graph->neighbors[i] = ll_create(sizeof(int));
		DIE(!graph->neighbors[i], "Neighbors create failed!\n");
	}
	graph->nodes = nodes;
	return graph;
}

void
lg_add_edge(list_graph_t* graph, int src, int dest)
{
	/* TODO */
	if (!graph->neighbors) {
		printf("No neighbors!\n");
		return;
	}
	int n = graph->neighbors[src]->size;
	ll_add_nth_node(graph->neighbors[src], n, &dest);
	n = graph->neighbors[dest]->size;
	ll_add_nth_node(graph->neighbors[dest], n, &src);
}

int
lg_has_edge(list_graph_t* graph, int src, int dest)
{
	/* TODO */
	if (!graph->neighbors) {
		printf("No neighbors!\n");
		return 0;
	}
	ll_node_t *node;
	for (unsigned int i = 0; i < graph->neighbors[src]->size; i++) {
		//iau toate elementele din lista nodului src
		node = get_nth_node(graph->neighbors[src], i);
		if (*(int*)node->data == dest) //daca exista nodul det printre ele
			return 1;
	}
	return 0;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node)
{
	/* TODO */
	if (!graph->neighbors) {
		printf("No neighbors!\n");
		return NULL;
	}
	return graph->neighbors[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest)
{
	/* TODO */
	if (!graph->neighbors[src]) {
		printf("No neighbors!\n");
		return;
	}
	ll_node_t *node1, *node2, *node;
	for (unsigned int i = 0; i < graph->neighbors[src]->size; i++) {
		node1 = get_nth_node(graph->neighbors[src], i);
		node2 = get_nth_node(graph->neighbors[dest], i);
		if (*(int*)node1->data == dest) {
			node = ll_remove_nth_node(graph->neighbors[src], i);
			free(node->data);
			free(node);
		}
		if (*(int*)node2->data == src) {
			node = ll_remove_nth_node(graph->neighbors[dest], i);
			free(node->data);
			free(node);
		}
	}
}

void
lg_free(list_graph_t* graph)
{
	/* TODO */
	if (!graph || !graph->neighbors) {
		printf("No graph or no neighbors!\n");
		return;
	}
	for (int i = 0; i < graph->nodes; i++) {
		ll_free(&graph->neighbors[i]);
	}
	free(graph->neighbors);
	free(graph);
}
