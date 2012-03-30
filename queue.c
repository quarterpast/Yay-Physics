#include "queue.h"

void enqueue(Queue *q, void *data) {
	pushBack(q, data);
}

void * dequeue(Queue *q) {
	return popFront(q);
}
