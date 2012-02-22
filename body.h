#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "vector.h"
#include "colour.h"

#ifndef BODY_H
#define BODY_H

#define G 1e-8
#define PATH_MOD(t) {if(t>=PATHLEN) t-=PATHLEN;}

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