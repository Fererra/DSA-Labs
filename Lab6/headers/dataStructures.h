#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

typedef struct Edge {
    int src, dest, weight;
    struct Edge *next;
} Edge;

typedef struct Vertex {
    int id;
    Edge *edges;
    struct Vertex *next;
} Vertex;

typedef struct Graph {
    int vertexCount;
    Vertex *vertices;
} Graph;

Graph *createGraph();
void addVertex(Graph*, int);
void addEdge(Graph*, int, int, int);
void freeGraph(Graph*);

#endif
