#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "dataStructures.h"
#include "matrix_utils.h"

#define MAX_EDGES 78

typedef struct {
    int u, v, weight;
} EdgeArr;

extern EdgeArr mstEdges[MAX_EDGES];  
extern int mstSize;  

int edgeCompare(const void*, const void*);
int find(int[], int);
void unite(int[], int[], int, int);
void prepareMST();
int kruskal(Graph*);

#endif