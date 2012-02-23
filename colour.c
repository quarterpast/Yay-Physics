#include "colour.h"

#include <stdlib.h>
#include <stdio.h>

/* Colour fadey functions */
void glColour(Colour *c) {
	glColor4dv(c);
}
Colour fade(Colour *c,int i) {
	Colour out = {
		c->r,
		c->g,
		c->b,
		c->a*((double)i)/((double)PATHLEN)
	};
	return out;
}
Colour randColour() {
	double r = 1.0-0.5*(((double)rand())/((double)RAND_MAX));
	double g = 1.0-0.5*(((double)rand())/((double)RAND_MAX));
	double b = 1.0-0.5*(((double)rand())/((double)RAND_MAX));
	double a = 1.0;
	Colour out = {r,g,b,a};
	//printColour(&out);
	return out;
}
void printColour(Colour *c) {
	printf("{%lf,%lf,%lf,%lf}\n",c->r,c->g,c->b,c->a);
}
