#include "physics.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "openglincludes.h"

#include "vector.h"
#include "body.h"
#include "unitcircle.h"

#include "list.h"

#define WIDTH 750
#define HEIGHT 750

#define TIMERMSECS 10
#define STEP 1.2

#define PATH_MOD(t) {if(t>=PATHLEN) t-=PATHLEN;}

//Body *b;
List *bodyList; // replaces b!!!
int bodies;
double steps = 2.0;
int width = WIDTH;
int height = HEIGHT;
int oldwidth = WIDTH;
int oldheight = HEIGHT;

static Vector *unitCircle;
static size_t numUnitCircleVertices;

void init() {
	srand(time(NULL));
	numUnitCircleVertices = 64;
	unitCircle = generateUnitCircle(numUnitCircleVertices);

	//b = (Body *)malloc(bodies*sizeof(Body));
	bodyList = newList();
	int i;
	for(i=0;i<bodies;++i) {
		Body *b = (Body *)malloc(sizeof(Body));
		*b = newBody(
			newVector(
				1-2*(float)rand()/(float)RAND_MAX,
				1-2*(float)rand()/(float)RAND_MAX
			),
			newVector(
				0.002-0.004*(float)rand()/(float)RAND_MAX,
				0.002-0.004*(float)rand()/(float)RAND_MAX
			),
			100*(float)rand()/(float)RAND_MAX
		);
		pushBack(bodyList, b);
	}
}

void timerFunc(int notUsed) {
	glutPostRedisplay();
}

/* GL/GLUT stuff */
void keyPressed (unsigned char key, int x, int y) {
	printf("%c\n",key);
	if(key == 'f') {
		#ifdef __FREEGLUT_STD_H__
		glutFullScreenToggle();
		#else
		if(
			glutGet(GLUT_WINDOW_WIDTH) == glutGet(GLUT_SCREEN_WIDTH) &&
			glutGet(GLUT_WINDOW_HEIGHT) == glutGet(GLUT_SCREEN_HEIGHT) &&
			glutGet(GLUT_WINDOW_X) == 0 &&
			glutGet(GLUT_WINDOW_Y) == 0
		) {
			glutReshapeWindow(oldwidth,oldheight);
		} else {
			glutFullScreen();
		}
		#endif
	}
	if(key == 'q') {
		#ifdef __FREEGLUT_STD_H__
		glutLeaveMainLoop();
		#else
		exit(0);// lol
		#endif
	}
	if(key == '+') {
		steps *= STEP;
	}
	if(key == '-') {
		steps /= STEP;
		if(steps < 1) steps = 1;
	}
	if(key == '\x1e') {
		// glutLeaveFullScreen();
	}
}
void reshape (int w, int h) {
	oldwidth = width;
	oldheight = height;
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void display() {
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	int k, j;
	// Body *bp;
	// Body *bBegin;
	// Body *bEnd;
	Body *b;
	ListIterator it;

	//Colour red = {1.0,0.0,0.0,0.5};
	glutTimerFunc(TIMERMSECS, timerFunc, 0);

	// bBegin = b + 1;
	// bEnd = b + bodies;
	for(k = 0; k < (int)steps; ++k) {
		for(it = bodyList->begin; bp != NULL; it = it->next) {
			b = it->data;
			b->acceleration = move(it, bodyList, bodies);
		}
		for(it = bodyList->begin; it != NULL; it = it->next) {
			b = it->data;
			b->velocity = vplus(&(b->velocity), &(b->acceleration));
			b->position = vplus(&(b->position), &(b->velocity));
			b->path.pos++;
			PATH_MOD(b->path.pos);
			b->path.point[b->path.pos] = b->position;
		}
	}
	for(it = bodyList->begin; it != NULL; it = it->next) {
		b = it->data;
		drawCircle(&(b->position), sqrt(b->mass), &(b->colour));
		traverse(b);
	}
	glutSwapBuffers();
}

Vector coordToScreen(Vector *pos) {
	Vector out = { pos->x*WIDTH/width, pos->y*HEIGHT/height };
	return out;
}

void traverse(Body *b) {
	int i,j;
	glBegin(GL_LINE_STRIP);
	for(i = 1; i<PATHLEN; i++) {
		j = i+bpath.pos;
		PATH_MOD(j);
		Vector px = coordToScreen(&(b->path.point[j]));
		glColor4f(
		          	b->colour.r,
		          	b->colour.g,
		          	b->colour.b,
		          	b->colour.a*((double)i)/((double)PATHLEN)
		          );
		glVertex2f(px.x,px.y);
	}
	glEnd(); // GL_LINE_STRIP
}

void drawCircle(Vector *pos, double r, Colour *c) {
	Vector sc = coordToScreen(pos);
	r = fmax(r,2);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();

	glTranslated(sc.x, sc.y, 0.0);
	glScaled(r / width, r / height, 1.0);
	
	glBegin(GL_POLYGON);
	glColor4dv((double *)c);
	int i;
	for (i = 0; i < numUnitCircleVertices; ++i) {
		glVertex2d(unitCircle[i].x, unitCircle[i].y);
	}
	glEnd(); //  GL_POLYGON
	
	glPopMatrix();
}
