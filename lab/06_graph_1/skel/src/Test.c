#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Stack.h"
#include "Queue.h"

#define MAX_NODES 10
#define INFINIT 999999

void
print_matrix_graph(matrix_graph_t* mg)
{
	/* TODO */
	for (int i = 0; i < mg->nodes; i++) {
		for (int j = 0; j < mg->nodes; j++) {
			printf("%d ", mg->matrix[i][j]);
		}
		printf("\n");
	}
}

void
print_list_graph(list_graph_t* lg)
{
	/* TODO */
	for (int i = 0; i < lg->nodes; i++) {
		printf("nodul %d: ", i);
		ll_print_int(lg->neighbors[i]);
		printf("\n");
	}
}

void
dfs_list_graph(list_graph_t* lg,
		int node,
		int* visited,
		int* t_desc,
		int* t_tin)
{
	/* TODO */
	int contor_timp = 0, v, vecin;

	for (int i = 0; i < lg->nodes; i++) {
		visited[i] = 0;
		t_desc[i] = 0;
		t_tin[i] = 0;	}

	stack_t *s = st_create(sizeof(int));

	contor_timp++;
	t_desc[node] = contor_timp;
	visited[node] = 1; //gri
	printf("%d ", node);

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
			t_desc[v] = contor_timp;
			visited[v] = 1; //gri
			printf("%d ", v);
			st_push(s, &v);
		} else {
			contor_timp++;
			t_tin[nodTop] = contor_timp;
			visited[nodTop] = 2; //negru
			st_pop(s);
		}
	}
	st_free(s);
}

void
dfs_matrix_graph(matrix_graph_t* mg,
		 int node,
		 int* visited,
		 int* t_desc,
		 int* t_tin)
{
	/* TODO */
	int contor_timp = 0, v, vecin;

	for (int i = 0; i < mg->nodes; i++) {
		visited[i] = 0;
		t_desc[i] = 0;
		t_tin[i] = 0;
	}

	stack_t *s = st_create(sizeof(int));

	contor_timp++;
	t_desc[node] = contor_timp;
	visited[node] = 1; //gri
	printf("%d ", node);

	st_push(s, &node);
	
	while (st_is_empty(s) == 0) {
		int nodTop = *(int*)st_peek(s);
		for (vecin = 0; vecin < mg->nodes; vecin++) {
			v = vecin;
			if (mg_has_edge(mg, vecin, nodTop) == 1 && visited[vecin] == 0) {
				break;
			}
		}
		if (mg_has_edge(mg, v, nodTop) == 1) {
			contor_timp++;
			t_desc[v] = contor_timp;
			visited[v] = 1; //gri
			printf("%d ", v);
			st_push(s, &v);
		} else {
			contor_timp++;
			t_tin[nodTop] = contor_timp;
			visited[nodTop] = 2; //negru
			st_pop(s);
		}
	}
	st_free(s);
}

void
bfs_list_graph(list_graph_t* lg, int node, int* color, int* parent)
{
	/* TODO */
	queue_t *q = q_create(sizeof(int), lg->nodes);
	int d[MAX_NODES]; //distanta

	for (int i = 0; i < lg->nodes; i++) {
		color[i] = 0; //alb
		d[i] = INFINIT;
		parent[i] = 0;
	}

	color[node] = 1; //gri
	d[node] = 0;
	q_enqueue(q, &node);
	printf("%d ", node);

	while ((q_is_empty(q)) == 0) {
		int v = *(int*)q_front(q);
		q_dequeue(q);
		for (int u = 0; u < lg->nodes; u++) {
			if (lg_has_edge(lg, v, u) == 1 && color[u] == 0) {
				color[u] = 1; //gri
				parent[u] = v;
				d[u] = d[v] + 1;
				q_enqueue(q, &u);
				printf("%d ", u);
			}
		}
		color[v] = 2; //negru
	}
	q_free(q);
}

void
bfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int* parent)
{
	/* TODO */
	queue_t *q = q_create(sizeof(int), mg->nodes);
	int d[MAX_NODES]; //distanta
	int i, u, v;

	for (i = 0; i < mg->nodes; i++) {
		color[i] = 0; //alb
		d[i] = INFINIT;
		parent[i] = 0;
	}

	color[node] = 1; //gri
	d[node] = 0;
	q_enqueue(q, &node);
	printf("%d ", node);

	while ((q_is_empty(q)) == 0) {
		v = *(int*)q_front(q);
		q_dequeue(q);
		for (u = 0; u < mg->nodes; u++) {
			if (mg_has_edge(mg, v, u) == 1 && color[u] == 0) {
				color[u] = 1; //gri
				parent[u] = v;
				d[u] = d[v] + 1;
				q_enqueue(q, &u);
				printf("%d ", u);
			}
		}
		color[v] = 2; //negru
	}
	q_free(q);
}

void
floyd_warshall(matrix_graph_t* mg, int weight[MAX_NODES][MAX_NODES])
{
	/* TODO BONUS */
	int n = mg->nodes, i, j, k, u, v;
	int dist[n][n];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			dist[i][j] = INFINIT;
		}
	}
	for (i = 0; i < n; i++) {
		dist[i][i] = 0;
	}
	for (u = 0; u < n; u++) {
		for (v = 0; v < n; v++) {
			if (mg_has_edge(mg, u, v) == 1) {
				dist[u][v] = weight[u][v];
			}
		}
	}		
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}	
			}
		}	
	}	

	for (u = 0; u < n; u++) {
		for (v = 0; v < n; v++) {
			printf("%d ", dist[u][v]);
		}
		printf("\n");
	}
}

int
main()
{
	int visited[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
	int parent[MAX_NODES];

	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	/*Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	/* test liste printate */
	printf("\nLista de adiacenta:\n");
	print_list_graph(lg);

	/* test dfs liste */
	printf("DFS liste de adiacenta:\n");
	dfs_list_graph(lg, numbers[0], visited, t_dest, t_fin);

	/* test bfs liste */
	printf("\nBFS liste de adiacenta:\n");
	dfs_list_graph(lg, numbers[0], visited, t_dest, t_fin);


	printf("\n-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	/* test dfs matrix graph */
	printf("\nDFS matrice de adiacenta:\n");
	mg_remove_edge(mg, numbers[3], numbers[2]);
	mg_add_edge(mg, numbers[0], numbers[4]);
	mg_add_edge(mg, numbers[0], numbers[5]);
	mg_add_edge(mg, numbers[0], numbers[2]);
	mg_add_edge(mg, numbers[1], numbers[2]);
	dfs_matrix_graph(mg, numbers[0], visited, t_dest, t_fin);
	printf("\n");

	/* test bfs matrix graph */
	printf("BFS matrice de adiacenta:\n");
	bfs_matrix_graph(mg, numbers[0], visited, parent);
	printf("\n");

	/*test matrice printata*/
	printf("Matricea de adiacenta:\n");
	print_matrix_graph(mg);

	/*test floyd warshall*/
	printf("\nFloyd Warshall:\n");
	int weight[MAX_NODES][MAX_NODES];
	for (int i = 0; i < MAX_NODES; i++) {
		for (int j = 0; j < MAX_NODES; j++) {
			weight[i][j] = 0;
		}
	}
	weight[0][4] = 2;
	weight[0][5] = 3;
	weight[0][2] = 1;
	weight[1][2] = 1;
	floyd_warshall(mg, weight);
	
	lg_free(lg);
	mg_free(mg);
	return 0;
}
