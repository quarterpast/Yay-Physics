#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	double x;
	double y;
	double z;
} Vector;

Vector newVector (double, double, double);
Vector vplus (Vector*, Vector*);
Vector vminus (Vector*, Vector*);
Vector smult (double, Vector*);
double norm (Vector*);
double distance (Vector*, Vector*);
Vector unit (Vector*);
double dot (Vector*, Vector*);

#endif // VECTOR_H
