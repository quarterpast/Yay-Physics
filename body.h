#ifndef BODY_H
#define BODY_H

#include <sys/types.h>

#include "vector.h"

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
	double gmass;
	double radius;
	Path path;
	Vector colour;
} Body;

Body newBody (Vector, Vector, double);
double newt (double, double);
Vector calculateAcceleration (Body*, Body*, int);
void collisionTest (Body*, Body*, int);
Vector bodyColour (void);

#endif // BODY_H
