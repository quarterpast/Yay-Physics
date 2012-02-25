#include "colour.h"

#include <stdlib.h>
#include <stdio.h>

Colour randColour() {
	double r = 1.0-0.5*(((double)rand())/((double)RAND_MAX));
	double g = 1.0-0.5*(((double)rand())/((double)RAND_MAX));
	double b = 1.0-0.5*(((double)rand())/((double)RAND_MAX));
	double a = 1.0;
	Colour out = {r,g,b,a};
	return out;
}
void printColour(Colour *c) {
	printf("{%lf,%lf,%lf,%lf}\n",c->r,c->g,c->b,c->a);
}
