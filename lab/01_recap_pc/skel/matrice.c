//Gheorghisor Ileana-Teodora 313CA
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
	int n, m, i, j;
	int **matrice;
	scanf("%d%d", &n, &m);
	// Alocarea dinamica a matricei
	matrice = (int**)calloc(m, sizeof(int*));
	for (i = 0; i < n; i++)
		matrice[i]= (int*)calloc(n, sizeof(int));

	//Rezolvarea problemei
	int x, y;
	while(scanf("%d%d", &x, &y)) {
		for (i = 0; i < x; i++)
			for (j = 0; j < y; j++) {
				matrice[i][j]++;
			}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			printf("%d ", matrice[i][j]);
		printf("\n");
	}

	//Eliberarea memoriei
		for( i = 0; i < n; i++)
			free(matrice[i]);
		free(matrice);

}