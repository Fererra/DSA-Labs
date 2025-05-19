#include <stdio.h>
#include "../headers/matrix_utils.h"
#include "../headers/dataStructures.h"
#include "../headers/kruskal.h"

#define N 12

void printInfo() {
  int **Aundir = generateAundir();
  int **W = generateW(Aundir);
  
  printf("\nUndirected Graph Matrix\n");
  printMatrix(Aundir);
  
  printf("\nW Matrix\n");
  printMatrix(W);
  
  Graph *g = createGraph();
    
  for (int i = 0; i < N; i++) {
    addVertex(g, i);
    for (int j = i; j < N; j++) {
      if (Aundir[i][j]) {
        addEdge(g, i, j, W[i][j]);
      }
    }
  }

  int cost = kruskal(g);
  printf("Minimum spanning tree cost: %d\n", cost);

  freeIntMatrix(Aundir);
  freeIntMatrix(W);
  freeGraph(g);
}

int main() {
  printInfo();
}