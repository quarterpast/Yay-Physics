#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector.h"
#include "body.h"

void timerFunc (int);
void reshape (int, int);
void keyboard (unsigned char, int, int);
void keyboardUp (unsigned char, int, int);
void keyboadOperations (void);
void special (int, int, int);
void specialUp (int, int, int);
void specialOperations (void);
void display (void);
void drawBody (Vector *, double, Vector *);
void drawPath (Body *);
void initialiseGL (void);
void initialiseSettings (void);
void initialiseArray (void);
void centraliseCoM (void);

#endif // PHYSICS_H
