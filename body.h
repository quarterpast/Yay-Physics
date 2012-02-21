#ifndef BODY_H
#define BODY_H 1

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
void circle(Vector*, double, Colour*);

#endif