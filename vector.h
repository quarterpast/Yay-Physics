#ifndef VECTOR_H
#define VECTOR_H 1

typedef struct {
	double x;
	double y;
} Vector;

Vector newVector(double, double); /* toil and trouble */
Vector vplus(Vector*, Vector*);
Vector vminus(Vector*, Vector*);
Vector smult(double, Vector*);
double norm(Vector *);
double distance(Vector*, Vector*);
Vector unit(Vector*);
Vector coordToScreen(Vector*);

#endif