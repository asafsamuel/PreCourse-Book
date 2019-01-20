#pragma once
#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include <stdio.h>
#include "Stack.h"

#define MAX_VALUE 9999

/* Algorithms */
int dfs(int** arr, int** flags, int x, int y, Stack* path, int heigth, int width);
void dijkstra(int** graph, int heigth, int width, int startNode, int target);

/* Run algorithms functions */
void runDFS(int** matrix, int heigth, int width);
void runDijkstra(int** matrix, int heigth, int width);

#endif // !_ALGORITHMS_H_