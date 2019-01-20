#include "Algorithms.h"

/*** Run algorithms functions ***/
/* runDFS function - use dfs algorithm for searching vertex in graph*/
void runDFS(int** matrix, int heigth, int width)
{
	// allocate memory
	int** flags = NULL;
	checkAllocation((flags = (int**)malloc(sizeof(int*)*heigth)));
	for (int i = 0; i < heigth; i++)
	{
		checkAllocation((flags[i] = (int*)malloc(sizeof(int)*width)));
		memset(flags[i], 0, sizeof(int)*width);
	}
	Stack* stack = initStack(heigth*width);

	// run algorithm
	dfs(matrix, flags, 0, 0, stack, heigth, width);

	// print
	printf("DFS: ");
	while (!isEmpty(stack))
		printf("%d<-", pop(stack));

	// free memory
	for (int i = 0; i < heigth; i++)
		free(flags[i]);
	free(flags);
}

/* runDijkstra function - use dijkstra algorithm for shortest path in graph*/
void runDijkstra(int** matrix, int heigth, int width)
{
	dijkstra(matrix, heigth, width, 0, heigth*width - 1);
}

/*** Algorithms ***/
int dfs(int** arr, int** flags, int x, int y, Stack* path, int heigth, int width)
{
	push(path, arr[y][x]);
	flags[y][x] = 1; // visited

	if ((y == heigth - 1) && (x == width - 1))
		return 1;

	if (y < heigth - 1 && flags[y + 1][x] == 0) // down
		if (dfs(arr, flags, x, y + 1, path, heigth, width) == 1)
			return 1;

	if (x < width - 1 && flags[y][x + 1] == 0) // right
		if (dfs(arr, flags, x + 1, y, path, heigth, width) == 1)
			return 1;

	if (x > 0 && flags[y][x - 1] == 0) // left
		if (dfs(arr, flags, x - 1, y, path, heigth, width) == 1)
			return 1;

	if (y > 0 && flags[y - 1][x] == 0) // up
		if (dfs(arr, flags, x, y - 1, path, heigth, width) == 1)
			return 1;

	flags[y][x] = 0; // not visited
	pop(path);
	return 0;
}

void dijkstra(int** graph, int heigth, int width, int startNode, int target)
{
	int** cost = NULL;
	int* distance = NULL;
	int* pred = NULL;
	int* visited = NULL;
	int n = heigth*width;
	int count, mindistance, nextnode, tmp;

	/* initialization */
	// allocate memory
	checkAllocation((cost = (int**)malloc(sizeof(int*)*n)));
	for (int i = 0; i < n; i++)
		checkAllocation((cost[i] = (int*)malloc(sizeof(int)*n)));

	checkAllocation((distance = (int*)malloc(sizeof(int)*n)));
	checkAllocation((pred = (int*)malloc(sizeof(int)*n)));
	checkAllocation((visited = (int*)malloc(sizeof(int)*n)));
	
	// create cost table
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				cost[i][j] = 0;
			else if ((((j - j%heigth) / heigth == (i - i%heigth) / heigth) && ((j%heigth == i%heigth + 1) || (j%heigth == i%heigth - 1))) || j == i - width || j == i + width)
				cost[i][j] = graph[(j - (j%heigth)) / width][j%width];
			else
				cost[i][j] = MAX_VALUE;
		}

	for (int i = 0; i< n; i++)
	{
		distance[i] = cost[startNode][i];
		pred[i] = startNode;
		visited[i] = 0;
	}

	distance[startNode] = 0;
	visited[startNode] = 1;
	count = 1;

	/* Start algorithm */
	while (count < n - 1)
	{
		mindistance = MAX_VALUE;
		for (int i = 0; i < n; i++)
		{
			if (distance[i] < mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextnode = i;
			}
		}

		visited[nextnode] = 1;
		for (int i = 0; i < n; i++)
		{
			if (!visited[i])
			{
				if (mindistance + cost[nextnode][i] < distance[i])
				{
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
			}
		}
		count++;
	}

	/* Print results */
	printf("Dijkstra: ");
	printf("\nDistance of #%d = %d", target, distance[target]);
	printf("\nPath = #%d", target);
	tmp = target;
	do
	{
		tmp = pred[tmp];
		printf(" <-#%d", tmp);
	} while (tmp != startNode);

	// free memory
	free(visited);
	free(pred);
	free(distance);
	for (int i = 0; i < heigth; i++)
		free(cost[i]);
	free(cost);
}