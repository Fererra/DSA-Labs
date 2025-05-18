#include <stdlib.h>
#include "../../headers/dataStructures.h"

Graph *createGraph() {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertexCount = 0;
    graph->vertices = NULL;
    return graph;
}

void addVertex(Graph *graph, int id) {
    Vertex *newVertex = (Vertex *)malloc(sizeof(Vertex));
    newVertex->id = id;
    newVertex->edges = NULL;
    newVertex->next = graph->vertices;
    graph->vertices = newVertex;
    graph->vertexCount++;
}

void addEdge(Graph *graph, int src, int dest, int weight) {
    Vertex *v = graph->vertices;
    while (v && v->id != src) v = v->next;
    if (v) {
        Edge *e = (Edge *)malloc(sizeof(Edge));
        e->src = src;
        e->dest = dest;
        e->weight = weight;
        e->next = v->edges;
        v->edges = e;
    }

    v = graph->vertices;
    while (v && v->id != dest) v = v->next;
    if (v) {
        Edge *e = (Edge *)malloc(sizeof(Edge));
        e->src = dest;
        e->dest = src;
        e->weight = weight;
        e->next = v->edges;
        v->edges = e;
    }
}
