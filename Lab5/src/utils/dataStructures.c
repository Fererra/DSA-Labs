#define N 12

typedef struct {
  int data[N];
  int front;
  int rear;
} Queue;

void initQueue(Queue *q) {
  q->front = 0;
  q->rear = 0;
}

int isQueueEmpty(Queue *q) {
  return q->front == q->rear;
}

void enqueue(Queue *q, int value) {
  if (q->rear < N) {
    q->data[q->rear++] = value;
  }
}

int dequeue(Queue *q) {
  if (!isQueueEmpty(q)) {
    return q->data[q->front++];
  }
  return -1;
}

typedef struct {
  int current;
  int parent;
} StackItem;

typedef struct {
  StackItem items[N];
  int top;
} Stack;

void initStack(Stack *s) {
  s->top = -1;
}

void push(Stack *s, int current, int parent) {
  if (s->top < N * N - 1) {
      s->items[++(s->top)] = (StackItem){.current = current, .parent = parent};
  }
}

StackItem pop(Stack *s) {
  if (s->top >= 0) {
      return s->items[(s->top)--];
  }
  return (StackItem){.current = -1, .parent = -1};
}

int isStackEmpty(Stack *s) {
  return s->top == -1;
}
