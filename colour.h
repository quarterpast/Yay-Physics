#ifndef COLOUR_H
#define COLOUR_H

typedef struct {
	double r;
	double g;
	double b;
	double a;
} Colour;

Colour randColour();
void printColour(Colour*);

#endif
