#ifndef PHYSICS_H
#define PHYSICS_H

#ifdef __linux__ 
#include <GL/freeglut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#error Not supported 
#endif // OS

#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "body.h"
#include "hlu.h"

#define INIT_WIN_WIDTH 640
#define INIT_WIN_HEIGHT 480
#define TIMERMSECS 10
#define STEP 1.2
#define PATH_MOD(t) { if (t >= PATHLEN) t -= PATHLEN;}

void timerFunc (int);
void reshape (int, int);
void keyboard (unsigned char, int, int);
void special (int, int, int);
void display (void);
void drawBody (Vector *, double, Vector *);
void drawPath (Body *b);
void initialiseSettings (void);
void initialiseArray (void);

#endif // PHYSICS_H
