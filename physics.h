#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __LINUX__ // OS
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else // WINDOWS
#error Not supported 
#endif // OS

#include "colour.h"
#include "vector.h"
#include "body.h"
#define G 1e-8
#define WIDTH 750
#define HEIGHT 750
#define TIMERMSECS 10
#define STEP 1.2
#define PATHLEN 1000
#define PATH_MOD(t) {if(t>=PATHLEN) t-=PATHLEN;}

void keyPressed(unsigned char, int, int);
void reshape(int, int);
void step();

#endif // PHYSICS_H

