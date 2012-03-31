#ifndef BODY_H
#define BODY_H

#include <sys/types.h>
#include <stdbool.h>

#include "vector.h"
#include "colour.h"
#include "list.h"

#define PATHLEN 200

typedef struct {
	Vector *point;
	size_t pos;
} Path;

typedef struct {
	Vector position;
	Vector velocity;
	Vector acceleration;
	double mass;
	Path path;
	Colour colour;
} Body;

Body newBody(Vector, Vector, double);
double newt(double, double);
bool collide(Body*, Body*, int, int);
Vector move(ListIterator thing, List *rest, int l);

#endif
