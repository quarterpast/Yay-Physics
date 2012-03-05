#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "openglincludes.h"
#include "vector.h"
#include "body.h"
#include "hlu.h"

#define INIT_WIN_WIDTH 640
#define INIT_WIN_HEIGHT 480
#define TIMERMSECS 10
#define STEP 1.2
#define CAMERA_SPEED 0.05
#define PATH_MOD(t) { if (t >= PATHLEN) t -= PATHLEN;}

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

#endif // PHYSICS_H
