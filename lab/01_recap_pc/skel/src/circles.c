#include <stdio.h>
#include <math.h>
#include "utils.h"

struct {
	int x;
	int y;
	int r;
} circle[100];

int main()
{
    int N, nr = 0, i, j;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
	    scanf("%d %d %d", &circle[i].x, &circle[i].y, &circle[i].r);
    }
    for (i = 0; i < N - 1; i++) 
	    for (j = i + 1; j < N; j++) {
		    double distanta;
		    distanta = sqrt(pow((circle[i].x - circle[j].x), 2) + pow((circle[i].y - circle[j].y), 2));
		    if (circle[i].r + circle[j].r >= distanta)
		    	nr++;
		    else if(circle[i].r > circle[j].r && circle[i].r - circle[j].r >= distanta)
		    	nr++;
		    else if(circle[i].r < circle[j].r && circle[j].r - circle[i].r >= distanta)
		    	nr++;
		  }
		  printf("%d", nr);
    return 0;
}
