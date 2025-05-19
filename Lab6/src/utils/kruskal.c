#include <stdlib.h>
#include <stdio.h>
#include "../../headers/dataStructures.h"
#include "../../headers/kruskal.h"

#define N 12

EdgeArr mstEdges[MAX_EDGES];
int mstSize = 0;

int edgeCompare(const void *a, const void *b) {
    return ((EdgeArr *)a)->weight - ((EdgeArr *)b)->weight;
}

int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unite(int parent[], int rank[], int x, int y) {
    x = find(parent, x);
    y = find(parent, y);

    if (rank[x] < rank[y])
        parent[x] = y;
    else if (rank[x] > rank[y])
        parent[y] = x;
    else {
        parent[y] = x;
        rank[x]++;
    }
}

Graph* prepareMST() {
    Graph *g = createGraph();
    for (int i = 0; i < N; i++) addVertex(g, i);

    int **Aundir = generateAundir();
    int **W = generateW(Aundir);

    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            if (Aundir[i][j])
                addEdge(g, i, j, W[i][j]);

    EdgeArr *allEdges = malloc(N * N * sizeof(EdgeArr));
    int totalEdges = 0;

    Vertex *v = g->vertices;
    while (v) {
        Edge *e = v->edges;
        while (e) {
            if (v->id < e->dest) {
                allEdges[totalEdges++] = (EdgeArr){v->id, e->dest, e->weight};
            }
            e = e->next;
        }
        v = v->next;
    }

    qsort(allEdges, totalEdges, sizeof(EdgeArr), edgeCompare);

    int parent[N], rank[N];
    for (int i = 0; i < N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < totalEdges && mstSize < N - 1; i++) {
        int u = allEdges[i].u;
        int v = allEdges[i].v;

        int set_u = find(parent, u);
        int set_v = find(parent, v);

        if (set_u != set_v) {
            mstEdges[mstSize++] = allEdges[i];
            unite(parent, rank, set_u, set_v);
        }
    }

    free(allEdges);

    return g;
}

int kruskal(Graph *graph) {
    int n = graph->vertexCount;
    int edgeCount = 0;
    EdgeArr *edges = malloc(sizeof(EdgeArr) * n * n);

    Vertex *v = graph->vertices;
    while (v) {
        Edge *e = v->edges;
        while (e) {
            if (v->id < e->dest) {
                edges[edgeCount++] = (EdgeArr){v->id, e->dest, e->weight};
            }
            e = e->next;
        }
        v = v->next;
    }

    qsort(edges, edgeCount, sizeof(EdgeArr), edgeCompare);

    int *parent = malloc(n * sizeof(int));
    int *rank = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    int cost = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = find(parent, edges[i].u);
        int v = find(parent, edges[i].v);

        if (u != v) {
            unite(parent, rank, u, v);
            cost += edges[i].weight;
            printf("Edge %d-%d weight %d\n", edges[i].u + 1, edges[i].v + 1, edges[i].weight);
        }
    }

    free(parent);
    free(rank);
    free(edges);
    return cost;
}
