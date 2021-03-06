#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "Algorithms.h"

#define HEIGHT 3
#define WIDTH 3
#define SIZE 5

#define WRONG_ARGUMENTS -1
#define CANNOT_OPEN_FILE -2
#define CANNOT_CLOSE_FILE -3
#define FAILED_MEMORY_ALLOCATION -4

void checkAllocation(void* pointer);
int readNumber(FILE* file);
void runAlgorithm(int** matrix, void(func)(int** graph, int h, int w));

int main(int argc, char* argv[])
{
	/* Local Variables */
	FILE* file = NULL;
	int** board = NULL;

	/* Check Argument Count*/
	if (argc <= 1)
	{
		printf("Usage: run.exe [file_path]\n");
		return WRONG_ARGUMENTS;
	}

	/* Open file */
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("Couldn't open %s.\n",argv[1]);
		return CANNOT_OPEN_FILE;
	}

	/* Initialize board */
	checkAllocation((board = (int**)malloc(sizeof(int*)*HEIGHT)));
	for (int i = 0; i < HEIGHT; i++)
	{
		checkAllocation((board[i] = (int*)malloc(sizeof(int)*WIDTH)));
		for (int j = 0; j < WIDTH; j++)
			board[i][j] = readNumber(file);
	}

	/* Close file */
	if (fclose(file) != 0)
	{
		printf("Couldn't close %s.\n", argv[1]);
		return CANNOT_CLOSE_FILE;
	}

	/* Find and print shortest path (run several algorithms) */
	runAlgorithm(board, runDFS); // DFS
	runAlgorithm(board, runDijkstra); // Dijkstra

	/* Free memory */
	for (int i = 0; i < HEIGHT; i++)
		free(board[i]);
	free(board);

    return 0;
}

/* readNumber function - read a number from a file */
int readNumber(FILE* file)
{
	char c;
	char buffer[SIZE];
	int index = 0;

	do
	{
		c = fgetc(file);
		buffer[index++] = c;
	} while (c != ' ' && c != '\n' && c != EOF);
	buffer[index - 1] = '\0';

	return atoi(buffer);
}

/* runAlgorithm function - find shortest path given matrix and algorithm */
void runAlgorithm(int** matrix, void(func)(int** graph, int h, int w))
{
	func(matrix, HEIGHT, WIDTH);
	printf("\n\n");
}

/* checkAllocation function - check if memory allocation succeeded*/
void checkAllocation(void* pointer)
{
	if (pointer == NULL)
	{
		printf("Memory allocation failed.\n");
		exit(FAILED_MEMORY_ALLOCATION);
	}
}