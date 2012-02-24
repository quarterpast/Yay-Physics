#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector.h"
#include "body.h"

void timerFunc(int);
void keyPressed(unsigned char, int, int);
void reshape(int, int);
void step();
Vector coordToScreen(Vector*);
void traverse(Body*);
void drawCircle(Vector *, double, Colour *);

#endif // PHYSICS_H
