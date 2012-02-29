#ifndef BODY_H
#define BODY_H

#include <sys/types.h>
#include <stdlib.h>
#include "vector.h"

#define PATHLEN 200
#define G 1e-8

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
	Vector colour;
} Body;

Body newBody (Vector, Vector, double);
double newt (double, double);
Vector move (Body*, Body*, int);
Vector bodyColour (void);

#endif
