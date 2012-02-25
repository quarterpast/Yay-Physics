#ifndef BODY_H
#define BODY_H

#include <sys/types.h>
#include <stdbool.h>

#include "vector.h"
#include "colour.h"

#define PATHLEN 50

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
Vector move(Body*, Body*, int, int);

#endif
