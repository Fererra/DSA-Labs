#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

typedef struct {
    int **treeMatrix;
    int **relativityMatrix;
} matrices;

int **generateAdir();
int **generateAundir();
void printMatrix(int**);
void freeIntMatrix(int**);
int getVertex(int, int**);
int getStartVertex(int**);
matrices bfs(int**);
matrices dfs(int**);
int *convertMatrixToVector(int**);
void printVector(int*);

#endif