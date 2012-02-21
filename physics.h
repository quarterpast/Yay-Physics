#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#include "colour.h"
#include "vector.h"
#include "path.h"
#include "body.h"
#define G 1e-8
#define WIDTH 750
#define HEIGHT 750
#define TIMERMSECS 1000/60
#define STEP 1.2
#define PATHLEN 1
#define PATH_MOD(t) {if(t>=PATHLEN) t-=PATHLEN;}

void keyPressed(unsigned char, int, int);
void reshape(int, int);
void step();