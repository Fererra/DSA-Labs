#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#define N 12

typedef struct {
    int data[N];
    int front;
    int rear;
} Queue;

void initQueue(Queue*);
int isQueueEmpty(Queue*);
void enqueue(Queue*, int);
int dequeue(Queue*);

typedef struct {
    int current;
    int parent;
} StackItem;

typedef struct {
    StackItem items[N];
    int top;
} Stack;

Stack* initStack(Stack*);
void push(Stack*, int, int);
StackItem pop(Stack*);
int isStackEmpty(Stack*);
void freeStack(Stack*);

#endif