#include <stdlib.h>
#include <stdio.h>

#define N 12

int findMax(int *arr) {
  int n = N;
  int max = arr[0];
  for (int i = 1; i < n; i++) {
      if (arr[i] > max) max = arr[i];
  }
  return max;
}

int findAverage(int start, int *arr) {
  int max = findMax(arr);

  return (75 + max) / 2;
}

int **getCoords(int start) {
  int n = N;

  int **coords = malloc(2 * sizeof(int*));
  for (int i = 0; i < 2; i++) {
      coords[i] = malloc(n * sizeof(int));
  }

  int step = 200;
  int side = (n - 1) / 3;

  coords[0][0] = start;
  coords[1][0] = start;

  for (int j = 1; j <= side; j++) {
      coords[0][j] = coords[0][j - 1] + step;
      coords[1][j] = start;
  }

  for (int j = side + 1; j <= 2 * side; j++) {
      coords[0][j] = coords[0][j - 1];
      coords[1][j] = coords[1][j - 1] + step;
  }

  for (int j = 2 * side + 1; j < n - 2; j++) {
      coords[0][j] = coords[0][j - 1] - step;
      coords[1][j] = coords[1][j - 1];
  }  

  int averageX = findAverage(start, coords[0]);
  int averageY = findAverage(start, coords[1]); 
    
  coords[0][n - 2] = start;
  coords[1][n - 2] = averageY;

  coords[0][n - 1] = averageX;
  coords[1][n - 1] = averageY;

  return coords;
}

void freeCoords(int **coords) {
  for (int i = 0; i < 2; i++) free(coords[i]);
  free(coords);
}
