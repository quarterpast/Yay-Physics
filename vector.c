#include "vector.h"

#include <math.h>

Vector newVector (double x, double y, double z) {

	Vector out = {x, y, z};
	return out;
}

Vector vplus (Vector *a, Vector *b) {

	Vector out = {a->x + b->x, a->y + b->y, a->z + b->z};
	return out;
}

Vector vminus (Vector *a, Vector *b) {

	Vector out = {a->x - b->x, a->y - b->y, a->z - b->z};
	return out;
}

Vector smult (double l, Vector *a) {

	Vector out = {(a->x) * l, (a->y) * l, (a->z) * l};
	return out;
}

double norm (Vector *a) {

	return sqrt (a->x * a->x + a->y * a->y + a->z * a->z);
}

double distance (Vector *a, Vector *b) {

	Vector d = vminus (a, b);
	return norm (&d);
}

Vector unit (Vector *a) {

	double n = norm (a);
	if (n == 0) {
		n = 1;
	}
	Vector out = {(a->x) / n, (a->y) / n, (a->z) / n};
	return out;
}

double dot (Vector *a, Vector *b) {

	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
