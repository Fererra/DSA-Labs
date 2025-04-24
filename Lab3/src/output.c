#include <stdio.h>
#include <../headers/matrix_utils.h>

int main() {
  int **Adir = generateAdir();
  int **Aundir = generateAundir();

  printf("Directed Graph Matrix\n");
  printMatrix(Adir);
  freeIntMatrix(Adir);

  printf("\nUndirected Graph Matrix\n");
  printMatrix(Aundir);
  freeIntMatrix(Aundir);
}