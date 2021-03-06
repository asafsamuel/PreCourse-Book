#include <stdio.h>
#include <time.h>
#include <windows.h>

/*
 * 1   0,1             ->  0  # Lonely
 * 1   4,5,6,7,8       ->  0  # Overcrowded
 * 1   2,3             ->  1  # Lives
 * 0   3               ->  1  # It takes three to give birth!
 * 0   0,1,2,4,5,6,7,8 ->  0  # Barren
*/

void playGame(int w, int h);
void show(unsigned int** u, int w, int h);
void evolve(unsigned int** u, int w, int h);

unsigned int** create2DArray(int x, int y);
void delete2DArray(unsigned int** arr, int x, int y);
void checkAllocation(void* pointer);

void main(int argc, char* argv[])
{
	/* local variables */
	int width = 0, height = 0;

	/* check argument count */
	if (argc <= 2)
	{
		printf("Usage: gameOfLife [width>0] [height>0]");
		return;
	}

	width = atoi(argv[1]);
	height = atoi(argv[2]);
	if (width <= 0 || height <= 0)
	{
		printf("Usage: gameOfLife [width>0] [height>0]");
		return;
	}

	/* start the game */
	playGame(width, height);
}

/* playGame function - play the game of life */
void playGame(int w, int h)
{
	/* create the universe */
	unsigned int** univ = create2DArray(w,h);

	/* randomize the universe */
	srand(time(NULL));
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			univ[i][j] = (unsigned int)(rand() % 2);

	/* play the game of life */
	while (1)
	{
		show(univ, w, h);
		evolve(univ, w, h);
		printf("\n");
		Sleep(10000);
	}
}

/* showBoard function - print the universe */
void show(unsigned int** u, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			printf("%d ", u[i][j]);
		printf("\n");
	}
}

/* evolve function - evolve to the next generation */
void evolve(unsigned int** u, int w, int h)
{
	unsigned int** newUniv = create2DArray(w, h);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			/* count neighbors and himself */
			int count = 0;
			for (int y = i-1; y <= i+1; y++)
				for (int x = j-1; x <= j+1; x++)
					if (u[(y + h) % h][(x + w) % w])
						count++;

			if (u[i][j])
				count--;
			newUniv[i][j] = (count == 3 || (count == 2 && u[i][j]));
		}
	}

	/* update the universe */
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			u[i][j] = newUniv[i][j];
	delete2DArray(newUniv, w, h);
}

/* create2DArray function - create 2-dimensional array */
unsigned int** create2DArray(int x, int y)
{
	unsigned int** arr = NULL;
	checkAllocation((arr = (unsigned int**)malloc(sizeof(unsigned int*)*y))); // univ = (unsigned int**)malloc(sizeof(unsigned int*)*h);
																			   // checkAllocation(univ);
	for (int i = 0; i < y; i++)
		checkAllocation((arr[i] = (unsigned int*)malloc(sizeof(unsigned int)*x))); // univ[i] = (unsigned int*)malloc(sizeof(unsigned int)*w);
																					// checkAllocation(univ[i]);
	return arr;
}

/* delete2DArray function - delete\free 2-dimensional array */
void delete2DArray(unsigned int** arr, int x, int y)
{
	if (arr != NULL)
	{
		for (int i = 0; i < y; i++)
			if(arr[i] != NULL)
				free(arr[i]);
		free(arr);
	}
}

/* checkAllocation function - check if allocation succeed. if not exit */
void checkAllocation(void* pointer)
{
	if (pointer == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}
}