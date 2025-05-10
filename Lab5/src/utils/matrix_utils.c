#include <stdlib.h>
#include <stdio.h>
#include "../headers/dataStructures.h"

#define SEED 4328
#define N 12
#define K 0.79

typedef struct {
  int **treeMatrix;
  int **relativityMatrix;
} matrices;

double **createDoubleMatrix() {
  int n = N;
  double **matrix = malloc(n * sizeof(double *));
  if (!matrix) {
    perror("malloc failed");
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
  int **matrix = malloc(n * sizeof(int *));
  if (!matrix) {
    perror("malloc failed");
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

int getVertex(int step, int **matrix) {
  int n = N;

  for (int i = 0; i < n; i++) {
    if (matrix[i][step]) return i;
  }

  return -1;
}

int getStartVertex(int **Adir) {
  int n = N; 

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (Adir[i][j]) return i;
    }
  }
}

matrices bfs(int **Adir) {
  int n = N;
  int **treeMatrix = createIntMatrix();
  int **relativityMatrix = createIntMatrix();

  int counter = 0;
  int *visited = calloc(n, sizeof(int));

  int startVertex = getStartVertex(Adir);

  Queue q;
  initQueue(&q);

  enqueue(&q, startVertex);
  visited[startVertex] = 1;

  while (!isQueueEmpty(&q)) {
    int current = dequeue(&q);
    relativityMatrix[current][counter++] = 1;

    for (int i = 0; i < n; i++) {
      if (Adir[current][i] && !visited[i]) {
        visited[i] = 1;
        enqueue(&q, i);
        treeMatrix[current][i] = 1;
      }
    }
  }

  free(visited);

  matrices result = {treeMatrix, relativityMatrix};
  return result;
}

matrices dfs(int **Adir) {
  int n = N;
  int **treeMatrix = createIntMatrix();
  int **relativityMatrix = createIntMatrix();
  int *visited = calloc(n, sizeof(int));
  int counter = 0;

  int start = getStartVertex(Adir);
  Stack stack;
  initStack(&stack);
  push(&stack, start, -1);

  while (!isStackEmpty(&stack)) {
      StackItem item = pop(&stack);
      int node = item.current;
      int parent = item.parent;

      if (visited[node]) continue;

      visited[node] = 1;
      relativityMatrix[node][counter++] = 1;

      if (parent != -1) {
          treeMatrix[parent][node] = 1;
      }

      for (int i = n - 1; i >= 0; i--) {
          if (Adir[node][i] && !visited[i]) {
              push(&stack, i, node);
          }
      }
  }

  free(visited);

  matrices result = {treeMatrix, relativityMatrix};
  return result;
}

int *convertMatrixToVector(int **matrix) {
  int n = N;
  int *vector = calloc(n, sizeof(int));

  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          if (matrix[i][j] == 1) {
              vector[i] = j + 1;
              break;
          }
      }
  }

  return vector;
}

void printVector(int *vector) {
  int n = N;
  printf("Old:");
  for (int i = 0; i < N; i++) printf("%3d ", i + 1);
  printf("\nNew:");
  for (int i = 0; i < N; i++) printf("%3d ", vector[i]);
  printf("\n");
}