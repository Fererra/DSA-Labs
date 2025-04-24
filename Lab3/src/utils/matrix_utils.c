#include <stdlib.h>
#include <stdio.h>

#define SEED 4328
#define N 12
#define K 0.67

double **createDoubleMatrix() {
  int n = N;
  double **matrix = malloc(n * sizeof(double *));
  if (!matrix) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(double));
    if (!matrix[i]) {
      perror("malloc failed");
      exit(EXIT_FAILURE);
    }
  }
  return matrix;
}

int **createIntMatrix() {
  int n = N;
  int **matrix = malloc(n * sizeof(int *));
  if (!matrix) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++) {
    matrix[i] = malloc(n * sizeof(int));
    if (!matrix[i]) {
      perror("malloc failed");
      exit(EXIT_FAILURE);
    }
  }
  return matrix;
}


double **randm() {
  srand(SEED);
  int n = N;
  double **temp = createDoubleMatrix();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      temp[i][j] = (double)rand() / (double)RAND_MAX * 2;
    }
  }
  return temp;
}

int **mulmr(double **matrix) {
  int n = N;
  int **Adir = createIntMatrix();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double a = matrix[i][j] * K;
      Adir[i][j] = a > 1 ? 1 : 0;
    }
  }

  return Adir;
}

void freeDoubleMatrix(double **matrix) {
  int n = N;
  for (int i = 0; i < n; i++) free(matrix[i]);
  free(matrix);
}

void freeIntMatrix(int **matrix) {
  int n = N;
  for (int i = 0; i < n; i++) free(matrix[i]);
  free(matrix);
}

int **generateAdir() {
  double **temp = randm();
  int **Adir = mulmr(temp);
  freeDoubleMatrix(temp);
  return Adir;
}


int **generateAundir() {
  int n = N;
  int **Adir = generateAdir();
  int **Aundir = createIntMatrix();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (Adir[i][j] || Adir[j][i]) {
        Aundir[i][j] = Aundir[j][i] = 1;
      }
    }
  }

  return Aundir;
}

void printMatrix(int **matrix) {
  int n = N;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}