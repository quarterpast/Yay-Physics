#ifndef OPENGLHEADERS_H
#define OPENGLHEADERS_H

#ifdef __linux__
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#error Not supported 
#endif 

#endif // OPENGLHEADERS_H
