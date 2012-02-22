#include "body.h"

#ifndef PHYSICS_H
#define PHYSICS_H

#define TIMERMSECS 10
#define STEP 1.2

void keyPressed(unsigned char, int, int);
void reshape(int, int);
void step();
Vector coordToScreen(Vector*);
void traverse(Body*);
void circle(Vector*, double, Colour*);

#endif // PHYSICS_H

