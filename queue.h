#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef List Queue;

void enqueue(Queue *q, void *data);
void * dequeue(Queue *q);

#endif /* QUEUE_H */
