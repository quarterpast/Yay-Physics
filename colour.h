#ifndef COLOUR_H
#define COLOUR_H 1

typedef struct {
	double r;
	double g;
	double b;
	double a;
} Colour;

void glColour(Colour*);
Colour fade(Colour*,int);
Colour randColour();

#endif