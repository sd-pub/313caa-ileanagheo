#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"


#define MAX_NODES	100
#define INF		0x3f3f3f3f

/**
 * Adaugati nodurile componentei conexe curente in lista component. 
 */
// static void
// dfs_connected_comps(
// 	list_graph_t *lg,
// 	int node,
// 	int *visited,
// 	linked_list_t *component
// ) {
// 	/* TODO */
// }

// static linked_list_t **
// connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
// {
// 	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
// 	DIE(!comps, "malloc comps failed");

// 	/* TODO: adaugati fiecare componenta conexa ca o noua lista in comps */

// 	return comps;
// }

static void
min_path(list_graph_t *lg, int start, int *dist)
{
	/* TODO */
	queue_t *q = q_create(sizeof(int), MAX_NODES);

	int p[MAX_NODES], visited[MAX_NODES];
	for (int u = 0; u < lg->nodes; u++) {
        visited[u] = 0;
        dist[u] = INF;
        p[u] = 0;
    }

    visited[start] = 1;
    dist[start] = 0;
    q_enqueue(q, &start);

    while ((q_is_empty(q)) == 0) {
		int v = *(int*)q_front(q);
		q_dequeue(q);
		for (int u = 0; u < lg->nodes; u++) {
			if (lg_has_edge(lg, v, u) == 1 && visited[u] == 0) {
				visited[u] = 1;
				p[u] = v;
				dist[u] = dist[v] + 1;
				q_enqueue(q, &u);
			}
		}
	}
	q_free(q);
}

static void
dfs_topo_sort(list_graph_t *lg, int node, int *visited, int tDesc[], int tFin[])
{
	/* TODO */
	int contor_timp = 0, v, vecin;

	stack_t *s = st_create(sizeof(int));

	contor_timp++;
	tDesc[node] = contor_timp;
	visited[node] = 1;

	st_push(s, &node);
	
	while (st_is_empty(s) == 0) {
		int nodTop = *(int*)st_peek(s);
		for (vecin = 0; vecin < lg->nodes; vecin++) {
			v = vecin;
			if (lg_has_edge(lg, vecin, nodTop) == 1 && visited[vecin] == 0) {
				break;
			}
		}
		if (lg_has_edge(lg, v, nodTop) == 1) {
			contor_timp++;
			tDesc[v] = contor_timp;
			visited[v] = 1;
			st_push(s, &v);
		} else {
			contor_timp++;
			tFin[nodTop] = contor_timp;
			st_pop(s);
		}
	}
	st_free(s);
}


static linked_list_t *
topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));
	
	/* TODO: adaugati nodurile in lista sorted, in ordinea corecta */
	int tDesc[MAX_NODES], tFin[MAX_NODES];

	for (int u = 0; u < lg->nodes; u++) {
        visited[u] = 0;
        tDesc[u] = 0;
        tFin[u] = 0;
    }

    for (int u = 0; u < lg->nodes; u++) {
        if (visited[u] != 1) {
        	ll_add_nth_node(sorted, 0, &u);
            dfs_topo_sort(lg, u, visited, tDesc, tFin);
        }
    }

    //Sortarea descrescatoare in functie de tFin
    ll_node_t *aux, *node_i, *node_j;
    int auxx;
    for (int i = 0; i < lg->nodes - 1; i++) {
    	for (int j = i + 1; j < lg->nodes; j++) {
    		if (tFin[i] < tFin[j]) {
    			node_j = get_nth_node(sorted, j);
    			node_i = get_nth_node(sorted, i);
    			memcpy(&aux, &node_i, sizeof(ll_node_t));
    			memcpy(&node_i, &node_j, sizeof(ll_node_t));
    			memcpy(&node_j, &aux, sizeof(ll_node_t));
    			auxx = tFin[i];
    			tFin[i] = tFin[j];
    			tFin[j] = auxx;
    		}
    	}
    }
	return sorted;
}

static int
check_bipartite(list_graph_t *lg, int *color)
{
	/* TODO: multimile vor avea culorile 1, respectiv 2 */
	queue_t *q = q_create(sizeof(int), lg->nodes);
	int node = 0;
	for (int i = 0; i < lg->nodes; i++) {
		color[i] = -1; //nivel nedefinit
	}
	color[node] = 2; //par
	q_enqueue(q, &node);

	while ((q_is_empty(q)) == 0) {
		int v = *(int*)q_front(q);
		q_dequeue(q);
		for (int u = 0; u < lg->nodes; u++) {
			if (lg_has_edge(lg, v, u) == 1 && color[u] == -1) {
				color[u] = (color[v] == 2) ? 1 : 2; //paritate opusa fata de v
				q_enqueue(q, &u);
			}
			if (lg_has_edge(lg, v, u) == 1 && color[u] == color[v]) {
				return 0;
			}
		}
	}
	q_free(q);
	return 1;
}

// static void
// test_connected_comp(void)
// {
// 	unsigned int num_comps, i, nodes, edges;
// 	int x, y;
// 	int visited[MAX_NODES] = {0};
// 	list_graph_t *lg;
// 	linked_list_t **comps;

// 	printf("UNDIRECTED graph for the connected components problem:\n");
// 	scanf("%u %u", &nodes, &edges);
// 	lg = lg_create(nodes);

// 	for (i = 0; i != edges; ++i) {
// 		scanf("%d %d", &x, &y);
// 		lg_add_edge(lg, x, y);
// 		lg_add_edge(lg, y, x);
// 	}

// 	comps = connected_components(lg, visited, &num_comps);

// 	printf("Found %d connected components:\n", num_comps);
// 	for (i = 0; i != num_comps; ++i) {
// 		ll_print_int(comps[i]);
// 		ll_free(comps + i);
// 	}
// 	printf("\n");

// 	free(comps);
// 	lg_free(lg);
// }

static void
test_min_dist(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int dist[MAX_NODES] = {0};
	list_graph_t *lg;

	printf("UNDIRECTED graph for the minimum distance problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	for (i = 0; i != nodes; ++i)
		dist[i] = INF;

	min_path(lg, 0, dist);

	printf("Minimum distances to node 0:\n");
	for (i = 0; i != nodes; ++i)
		printf("%u: %d\n", i, dist[i]);
	printf("\n");

	lg_free(lg);
}

static void
test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	printf("Topologically sorted nodes:\n");
	ll_print_int(sorted);
	printf("\n");

	ll_free(&sorted);
	lg_free(lg);
}

static
void test_bipartite(void)
{
	unsigned int i, nodes, edges;
	int color[MAX_NODES] = {0};
	int x, y;
	list_graph_t *lg;

	printf("UNDIRECTED graph for the bipartite graph problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i) {
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}
	
	if (check_bipartite(lg, color)) {
		printf("Nodes with colour 1:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 1)
				printf("%d ", i);
		printf("\nNodes with colour 2:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 2)
				printf("%d ", i);
		printf("\n");
	} else
		printf("The graph is not bipartite\n");

	lg_free(lg);
}

int
main(void)
{
	/* Ex 1 */
	// test_connected_comp();

	/* Ex 2 */
	test_min_dist();

	/* Ex 3 */
	test_topo_sort();

	/* Ex 4 */
	test_bipartite();

	return 0;
}
