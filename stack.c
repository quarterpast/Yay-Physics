#include "stack.h"

void push(Stack *s, void *data) {
	pushBack(s, data);
}

void * pop(Stack *s) {
	return popBack(s, data);
}
