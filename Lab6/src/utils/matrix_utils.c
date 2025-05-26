#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../headers/dataStructures.h"

#define SEED 4328
#define N 12
#define K 0.89

double **createDoubleMatrix() {
  int n = N;
  double **matrix = calloc(n, sizeof(double *));
  if (!matrix) {
    perror("calloc failed");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++) {
    matrix[i] = calloc(n, sizeof(double));
    if (!matrix[i]) {
      perror("calloc failed");
      exit(EXIT_FAILURE);
    }
  }
  return matrix;
}

int **createIntMatrix() {
  int n = N;
  int **matrix = calloc(n, sizeof(int *));
  if (!matrix) {
    perror("calloc failed");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n; i++) {
    matrix[i] = calloc(n, sizeof(int));
    if (!matrix[i]) {
      perror("calloc failed");
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
      temp[i][j] = (double)rand() / (double)RAND_MAX * 2.0;
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
      printf("%4d ", matrix[i][j]);
    }

    printf("\n");
  }
}

int **generateC(double **B, int **Aundir) {
  int n = N;
  int **C = createIntMatrix();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = (int)ceil(B[i][j] * 100 * Aundir[i][j]);
    }
  }

  return C;
}

int **generateD(int **C) {
  int n = N;
  int **D = createIntMatrix();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      D[i][j] = C[i][j] > 0 ? 1 : 0;
    }
  }

  return D;
}

int **generateH(int **D) {
  int n = N;
  int **H = createIntMatrix();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      H[i][j] = (D[i][j] != D[j][i]) ? 1 : 0;
    }
  }

  return H;
}

int **generateTr() {
  int n = N;
  int **Tr = createIntMatrix();

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      Tr[i][j] = 1;
    }
  }
  
  return Tr;
}

int **generateW(int **Aundir) {
  int n = N;

  double **B = randm();
  int **C = generateC(B, Aundir);
  int **D = generateD(C);
  int **H = generateH(D);
  int **Tr = generateTr();

  int **W = createIntMatrix();

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      W[i][j] = W[j][i] = (D[i][j] + H[i][j] * Tr[i][j]) * C[i][j];
    }
  }

  return W;
}