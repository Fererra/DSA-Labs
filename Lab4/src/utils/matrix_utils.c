#include <stdlib.h>
#include <stdio.h>

#define SEED 4328
#define N 12

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
      temp[i][j] = (double)rand() / (double)RAND_MAX * 2;
    }
  }
  return temp;
}

int **mulmr(double **matrix, double K) {
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

int **generateAdir(double K) {
  double **temp = randm();
  int **Adir = mulmr(temp, K);
  freeDoubleMatrix(temp);
  return Adir;
}

int **generateAundir(double K) {
  int n = N;
  int **Adir = generateAdir(K);
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

int *computeOutDegrees(int **Adir) {
  int n = N;
  int *outdegrees = calloc(n, sizeof(int));

  for (int i = 0; i < n; i++) {
    outdegrees[i] = 0;
    for (int j = 0; j < n; j++) {
      if (Adir[i][j]) outdegrees[i]++;
    }
  }

  return outdegrees;
}

int *computeInDegrees(int **Adir) {
  int n = N;
  int *indegrees = calloc(n, sizeof(int));

  for (int j = 0; j < n; j++) {
    indegrees[j] = 0;
    for (int i = 0; i < n; i++) {
      if (Adir[i][j]) indegrees[j]++;
    }
  }
  return indegrees;
}

int *computeDegrees(int **Aundir) {
  int n = N;
  int *degrees = calloc(n, sizeof(int));
  
  for (int i = 0; i < n; i++) {
    degrees[i] = 0;
    for (int j = 0; j < n; j++) {
      if (Aundir[i][j]) degrees[i]++;
    }
  }
  return degrees;
}

int *computeTotalDegrees(int *outdegrees, int *indegrees) {
  int n = N;
  int *degrees = calloc(n, sizeof(int));

  for (int i = 0; i < n; i++) {
    degrees[i] = outdegrees[i] + indegrees[i];
  }
  
  return degrees;
}

void printDegrees(int *degrees) {
  int n = N;

  for (int i = 0; i < n; i++) {
    printf("%d ", degrees[i]);
  }
}

int isGraphRegular(int *degrees) {
  int n = N;
  int degree = degrees[0];

  for (int i = 1; i < n; i++) {
    if (degrees[i] != degree) return 0;
  }
  return 1;
}

int *computeIsolatedVertices(int *degrees, int *count) {
  int n = N;
  int *isolated = calloc(n, sizeof(int));
  *count = 0;

  for (int i = 0; i < n; i++) {
    if (degrees[i] == 0) {
      isolated[(*count)++] = i + 1;
    }
  }

  return isolated;
}

int *computePendantVertices(int *degrees, int *count) {
  int n = N;
  int *pendant = calloc(n, sizeof(int));
  *count = 0;

  for (int i = 0; i < n; i++) {
    if (degrees[i] == 1) {
      pendant[(*count)++] = i + 1;
    }
  }

  return pendant;
}

void outputVertices(int *vertices, int count) {
  for (int i = 0; i < count; i++) {
    printf("%d ", vertices[i]);
  }
  printf("\n");
}

void printVertexGroup(const char *label, int *vertices, int count) {
  printf("%s: ", label);
  if (count > 0)
      outputVertices(vertices, count);
  else
      printf("none\n");
}

int **multiplyMatrices(int **A, int **B) {
  int n = N;
  int **result = createIntMatrix();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return result;
}

void printPathsLength2(int **Adir, int **A2) {
  int n = N;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (A2[i][j] > 0) {
        for (int k = 0; k < n; k++) {
          if (Adir[i][k] && Adir[k][j]) {
            printf("%d - %d - %d, ", i + 1, k + 1, j + 1);
          }
        }
        printf("\n");
      }
    }
  }
}

void printPathsLength3(int **Adir, int **A3) {
  int n = N;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (A3[i][j] > 0) {
        for (int k = 0; k < n; k++) {
          if (Adir[i][k]) {
            for (int l = 0; l < n; l++) {
              if (Adir[k][l] && Adir[l][j]) {
                printf("%d - %d - %d - %d, ", i + 1, k + 1, l + 1, j + 1);
              }
            }
          }
        }
        printf("\n");
      }
    }
  }
}

int **copyMatrix(int **src) {
  int n = N;
  int **copy = createIntMatrix();

  for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
          copy[i][j] = src[i][j];
  
  return copy;
}

int **addMatrices(int **A, int **B) {
  int n = N;
  int **result = createIntMatrix();

  for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
          result[i][j] = A[i][j] + B[i][j];

  return result;
}

void booleanizeMatrix(int **matrix) {
  int n = N;

  for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
          matrix[i][j] = matrix[i][j] > 0 ? 1 : 0;
}

int **identityMatrix() {
  int n = N;
  int **I = createIntMatrix();

  for (int i = 0; i < n; i++)
      I[i][i] = 1;

  return I;
}

int **computeReachability(int **A) {
  int n = N;

  int **reachabilityMatrix = identityMatrix();
  int **Am = copyMatrix(A);

  for (int k = 1; k < n; k++) {
      int **temp = addMatrices(reachabilityMatrix, Am);
      freeIntMatrix(reachabilityMatrix);
      reachabilityMatrix = temp;

      int **nextPower = multiplyMatrices(Am, A);
      freeIntMatrix(Am);
      Am = nextPower;
  }

  booleanizeMatrix(reachabilityMatrix);
  freeIntMatrix(Am);
  return reachabilityMatrix;
}

int **transposeMatrix(int **matrix) {
  int n = N;
  int **T = createIntMatrix();

  for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
          T[j][i] = matrix[i][j];

  return T;
}

int **elementwiseMultiply(int **A, int **B) {
  int n = N;
  int **result = createIntMatrix();

  for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
          result[i][j] = A[i][j] && B[i][j];

  return result;
}

int **computeStrongConnectivity(int **reachabilityMatrix) {
    int **transposedMatrix = transposeMatrix(reachabilityMatrix);
    int **strongConnectivityMatrix = elementwiseMultiply(reachabilityMatrix, transposedMatrix);
    freeIntMatrix(transposedMatrix);
    return strongConnectivityMatrix;
}

void dfs(int **strongConnectivityMatrix, int vertex, int *component, int *visited) {
  int n = N;
  visited[vertex] = 1;
  component[vertex] = 1;

  for (int i = 0; i < n; i++) {
      if (!visited[i] && strongConnectivityMatrix[vertex][i]) {
          dfs(strongConnectivityMatrix, i, component, visited);
      }
  }
}

int **computeStronglyConnectedComponents(int **strongConnectivityMatrix, int *componentCount) {
    int n = N;
    int *visited = calloc(n, sizeof(int));

    int **components = calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        components[i] = calloc(n, sizeof(int));
    }

    int count = 0;

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            dfs(strongConnectivityMatrix, vertex, components[count], visited);
            count++;
        }
    }

    *componentCount = count;
    free(visited);
    return components;
}

void printComponents(int **components, int componentCount) {
  int n = N;

  for (int i = 0; i < componentCount; i++) {
      printf("Component %d: ", i + 1);
      for (int j = 0; j < n; j++) {
          if (components[i][j]) {
              printf("%d ", j + 1);
          }
      }
      printf("\n");
  }
}

int **generateAcondensation(int **A, int **components, int componentCount) {
  int n = N;
  int **condensation = calloc(componentCount, sizeof(int *));
  for (int i = 0; i < componentCount; i++)
      condensation[i] = calloc(componentCount, sizeof(int));

  int *vertexToComponent = calloc(n, sizeof(int));
  for (int comp = 0; comp < componentCount; comp++) {
      for (int v = 0; v < n; v++) {
          if (components[comp][v]) {
              vertexToComponent[v] = comp;
          }
      }
  }

  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          if (A[i][j]) {
              int from = vertexToComponent[i];
              int to = vertexToComponent[j];
              if (from != to) {
                  condensation[from][to] = 1;
              }
          }
      }
  }

  free(vertexToComponent);
  return condensation;
}

void printCondensationMatrix(int **matrix, int size) {
  for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
          printf("%d ", matrix[i][j]);
      }
      printf("\n");
  }
}

int **generateAcondensationByK(double K, int *componentCount) {
  int **Adir = generateAdir(K);
  int **reachabilityMatrix = computeReachability(Adir);
  int **strongConnectivityMatrix = computeStrongConnectivity(reachabilityMatrix);
  int **components = computeStronglyConnectedComponents(strongConnectivityMatrix, componentCount);
  int **Acondensation = generateAcondensation(Adir, components, *componentCount);

  freeIntMatrix(Adir);
  freeIntMatrix(reachabilityMatrix);
  freeIntMatrix(strongConnectivityMatrix);

  for (int i = 0; i < *componentCount; i++) {
    free(components[i]);
  }
  free(components);

  return Acondensation;
}