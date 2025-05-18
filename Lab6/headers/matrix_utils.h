#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

double **randm();
int **generateAdir();
int **generateAundir();
void printMatrix(int**);
void freeIntMatrix(int**);
void freeDoubleMatrix(double**);

int **generateC(double**, int**);
int **generateD(int**);
int **generateH(int**);
int **generateTr();
int **addMatrices(int**, int**);
int **generateW(int **);

#endif