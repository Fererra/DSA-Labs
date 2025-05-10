#include <stdio.h>
#include <stdlib.h>
#include "../headers/matrix_utils.h"

void printAdir() {
  int **Adir = generateAdir();
  printf("\nAdjacency Matrix\n");
  printMatrix(Adir);
  freeIntMatrix(Adir);
}

void printBFS() {
  int **Adir = generateAdir();
  matrices searchMatrices = bfs(Adir);
  int *relabel = convertMatrixToVector(searchMatrices.relativityMatrix);

  printf("\n=== Breadth-First Search ===\n");

  printf("\nSearch Tree Matrix\n");
  printMatrix(searchMatrices.treeMatrix);

  printf("\nRelativity Matrix\n");
  printMatrix(searchMatrices.relativityMatrix);

  printf("\nCorrespondence vector\n");
  printVector(relabel);

  free(relabel);
  freeIntMatrix(Adir);
  freeIntMatrix(searchMatrices.treeMatrix);
  freeIntMatrix(searchMatrices.relativityMatrix);
}

void printDFS() {
  int **Adir = generateAdir();
  matrices searchMatrices = dfs(Adir);
  int *relabel = convertMatrixToVector(searchMatrices.relativityMatrix);

  printf("\n=== Depth-First Search ===\n");

  printf("\nSearch Tree Matrix\n");
  printMatrix(searchMatrices.treeMatrix);

  printf("\nRelativity Matrix\n");
  printMatrix(searchMatrices.relativityMatrix);

  printf("\nCorrespondence vector\n");
  printVector(relabel);

  free(relabel);
  freeIntMatrix(Adir);
  freeIntMatrix(searchMatrices.treeMatrix);
  freeIntMatrix(searchMatrices.relativityMatrix);
}

int main() {
  printAdir();
  printBFS();
  printDFS();
}