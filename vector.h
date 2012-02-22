#include <math.h>

#ifdef __linux__ // OS
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else // WINDOWS
#error Not supported 
#endif // OS

// #ifndef VECTOR_H
// #define VECTOR_H 1

#define WIDTH 750
#define HEIGHT 750

typedef struct {
	double x;
	double y;
} Vector;

Vector newVector(double, double); /* toil and trouble */
Vector vplus(Vector*, Vector*);
Vector vminus(Vector*, Vector*);
Vector smult(double, Vector*);
double norm(Vector *);
double distance(Vector*, Vector*);
Vector unit(Vector*);
Vector coordToScreen(Vector*);

// #endif