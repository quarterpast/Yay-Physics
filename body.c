#include "body.h"

Body newBody (Vector pos, Vector vel, double mass) {

	Vector *arr = malloc (PATHLEN * sizeof (Vector));
	int i;
	for (i = 0; i < PATHLEN; i++) {
		arr[i] = pos;
	}
	Path path = {
		arr,
		0
	};
	double radius = sqrt (mass) / 100;
	Body out = {
		pos,
		vel,
		{0, 0, 0},
		mass,
		radius,
		path,
		bodyColour ()
	};
	return out;
}

double newt (double m, double r) {

	return G * m / (r * r);
}

Vector move (Body* thing, Body* rest, int l) {

	double n, r;
	Vector ds = {0, 0, 0}, diff, u, m;
	Body b;
	Body *restEnd = rest + l;
	for(; rest != restEnd; ++rest) {
		if (rest == thing) continue;
		b = *rest;
		r = distance (&(thing->position), &(b.position));
		n = newt (rest->mass, r);
		diff = vminus (&(b.position), &(thing->position));
		u = unit (&diff);
		m = smult (n, &u);
		ds = vplus (&ds, &m);
	}
	return ds;
}

int collisionTest (Body* thing, Body* rest, int l) {

	int isColliding = 0;
	double r;
	Body b;
	Body *restEnd = rest + l;
	for(; rest != restEnd; ++rest) {
		if (rest == thing) continue;
		b = *rest;
		r = distance (&(thing->position), &(b.position));
		if (r < (thing->radius + b.radius)) isColliding = 1;
	}
	return isColliding;
}

Vector bodyColour (void) {

	double rep = 2.0 * RAND_MAX;
	double r = 1.0 - rand () / rep;
	double g = 1.0 - rand () / rep;
	double b = 1.0 - rand () / rep;
	Vector out = {r, g, b};
	return out;
}
