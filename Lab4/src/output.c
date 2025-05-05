#include <stdio.h>
#include <stdlib.h>
#include "../headers/matrix_utils.h"

#define K1 0.6
#define K2 0.68

void directedGraphInfo() {
  int **Adir = generateAdir(K1);
  int *outdegrees = computeOutDegrees(Adir);
  int *indegrees = computeInDegrees(Adir);
  int *totalDegrees = computeTotalDegrees(outdegrees, indegrees);

  int isolatedCount, pendantCount;

  int *isolatedVertices = computeIsolatedVertices(totalDegrees, &isolatedCount);
  int *pendantVertices = computePendantVertices(totalDegrees, &pendantCount);

  printf("\n=== Directed Graph Info ===\n");

  printf("\nAdjacency matrix\n");
  printMatrix(Adir);

  printf("\nDegrees of graph vertices\n");
  printf("Outdegrees of each vertex: ");
  printDegrees(outdegrees);
  printf("\nIndegrees of each vertex: ");
  printDegrees(indegrees);

  printf("\nGraph regularity: ");
  if (isGraphRegular(totalDegrees)) {
    printf("%d\n", totalDegrees[0]);
  } else {
    printf("irregular\n");
  }

  printf("\nList of vertices\n");
  printVertexGroup("Isolated", isolatedVertices, isolatedCount);
  printVertexGroup("Pendant", pendantVertices, pendantCount);

  freeIntMatrix(Adir);
  free(outdegrees);
  free(indegrees);
  free(totalDegrees);
  free(isolatedVertices);
  free(pendantVertices);
}

void undirectedGraphInfo() {
  int **Aundir = generateAundir(K1);
  int *degrees = computeDegrees(Aundir);

  int isolatedCount, pendantCount;

  int *isolatedVertices = computeIsolatedVertices(degrees, &isolatedCount);
  int *pendantVertices = computePendantVertices(degrees, &pendantCount);

  printf("\n=== Undirected Graph Info ===\n");
 
  printf("\nAdjacency matrix\n");
  printMatrix(Aundir);

  printf("\nDegrees of graph vertices: ");
  printDegrees(degrees);

  printf("\nGraph regularity: ");
  if (isGraphRegular(degrees)) {
    printf("%d\n", degrees[0]);
  } else {
    printf("irregular\n");
  }

  printf("\nList of vertices\n");
  printVertexGroup("Isolated", isolatedVertices, isolatedCount);
  printVertexGroup("Pendant", pendantVertices, pendantCount);

  
  freeIntMatrix(Aundir);
  free(degrees);
  free(isolatedVertices);
  free(pendantVertices);
}

void modifiedGraphInfo() {
  int **Adir = generateAdir(K2);
  int **A2 = multiplyMatrices(Adir, Adir);
  int **A3 = multiplyMatrices(A2, Adir);
  int *outdegrees = computeOutDegrees(Adir);
  int *indegrees = computeInDegrees(Adir);
  int *totalDegrees = computeTotalDegrees(outdegrees, indegrees);
  
  int isolatedCount, pendantCount, componentCount;

  int *isolatedVertices = computeIsolatedVertices(totalDegrees, &isolatedCount);
  int *pendantVertices = computePendantVertices(totalDegrees, &pendantCount);

  int **reachabilityMatrix = computeReachability(Adir);
  int **strongConnectivityMatrix = computeStrongConnectivity(reachabilityMatrix);
  int **stronglyConnectedComponents = computeStronglyConnectedComponents(strongConnectivityMatrix, &componentCount);

  int **Acondensation = generateAcondensation(Adir, stronglyConnectedComponents, componentCount);

  printf("\n=== Modified Graph Info ===\n");

  printf("\nAdjacency matrix\n");
  printMatrix(Adir);

  printf("\nDegrees of graph vertices\n");
  printf("Outdegrees of each vertex: ");
  printDegrees(outdegrees);
  printf("\nIndegrees of each vertex: ");
  printDegrees(indegrees);

  printf("\nGraph regularity: ");
  if (isGraphRegular(totalDegrees)) {
    printf("%d\n", totalDegrees[0]);
  } else {
    printf("irregular\n");
  }

  printf("\nList of vertices\n");
  printVertexGroup("Isolated", isolatedVertices, isolatedCount);
  printVertexGroup("Pendant", pendantVertices, pendantCount);

  printf("\nMatrix A^2:\n");
  printMatrix(A2);

  printf("\nPaths of Length 2\n");
  printPathsLength2(Adir, A2);

  printf("\nMatrix A^3:\n");
  printMatrix(A3);

  printf("\nPaths of Length 3\n");
  printPathsLength3(Adir, A3);

  printf("\nReachability Matrix\n");
  printMatrix(reachabilityMatrix);

  printf("\nStrong Connected Matrix\n");
  printMatrix(strongConnectivityMatrix);

  printf("\nStrongly Connected Components\n");
  printComponents(stronglyConnectedComponents, componentCount);

  printf("\n**Condensation Graph Adjacency Matrix**\n");
  printCondensationMatrix(Acondensation, componentCount);

  freeIntMatrix(Adir);
  freeIntMatrix(A2);
  freeIntMatrix(A3);
  freeIntMatrix(reachabilityMatrix);
  freeIntMatrix(strongConnectivityMatrix);
  freeIntMatrix(Acondensation);
  free(outdegrees);
  free(indegrees);
  free(totalDegrees);
  free(isolatedVertices);
  free(pendantVertices);
  free(stronglyConnectedComponents);
}

int main() {
  directedGraphInfo();
  undirectedGraphInfo();
  modifiedGraphInfo();
}