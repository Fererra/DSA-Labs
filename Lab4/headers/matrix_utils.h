#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

int **generateAdir(double);
int **generateAundir(double);
void printMatrix(int**);
void freeIntMatrix(int**);

int *computeOutDegrees(int**);
int *computeInDegrees(int**);
int *computeDegrees(int**);
int *computeTotalDegrees(int*, int*);
void printDegrees(int*);

int isGraphRegular(int*);

int *computeIsolatedVertices(int*, int*);
int *computePendantVertices(int*, int*);
void outputVertices(int*, int);
void printVertexGroup(const char*, int*, int);

int **multiplyMatrices(int**, int**);
void printPathsLength2(int**, int**);
void printPathsLength3(int**, int**);

int **computeReachability(int**);
int **computeStrongConnectivity(int**);
int **computeStronglyConnectedComponents(int**, int*);
void printComponents(int**, int);
int **generateAcondensation(int**, int**, int);
int **generateAcondensationByK(double, int*);
void printCondensationMatrix(int**, int);

#endif