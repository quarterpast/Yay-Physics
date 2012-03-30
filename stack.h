#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef List Stack;

void push(Stack *s, void *data);
void * pop(Stack *s);

#endif /* STACK_H */
