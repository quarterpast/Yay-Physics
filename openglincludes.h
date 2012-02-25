#ifndef OPENGLHEADERS_H
#define OPENGLHEADERS_H

#ifdef __linux__ // OS
#include <GL/glut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else // WINDOWS
#error Not supported 
#endif // OS

#endif // OPENGLHEADERS_H
