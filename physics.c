#include "physics.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "openglincludes.h"

#include "vector.h"
#include "body.h"
#include "unitcircle.h"

#define WIDTH 750
#define HEIGHT 750

#define TIMERMSECS 10
#define STEP 1.2

#define PATH_MOD(t) {if(t>=PATHLEN) t-=PATHLEN;}

Body *b;
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

	b = (Body *)malloc(bodies*sizeof(Body));
	int i;
	for(i=0;i<bodies;++i) {
		b[i] = newBody(
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
	}
	b[0] = newBody(newVector(0,0.0001),newVector(0,0),2000);
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
	Body *bp;
	Body *bBegin;
	Body *bEnd;
	//Colour red = {1.0,0.0,0.0,0.5};
	glutTimerFunc(TIMERMSECS, timerFunc, 0);

	bBegin = b + 1;
	bEnd = b + bodies;
	for(k = 0; k < (int)steps; ++k) {
		for(bp = bBegin, j = 1; bp != bEnd; ++bp) {
			bp->acceleration = move(bp, b, bodies);
		}
		for(bp = bBegin; bp != bEnd; ++bp) {
			bp->velocity = vplus(&(bp->velocity), &(bp->acceleration));
			bp->position = vplus(&(bp->position), &(bp->velocity));
			bp->path.pos++;
			PATH_MOD(bp->path.pos);
			bp->path.point[bp->path.pos] = bp->position;
		}
	}
	for(bp = b; bp != bEnd; ++bp) {
		//if(collide(&(b[j]),b,bodies,j)) b[j].colour = red;
		drawCircle(&(bp->position), sqrt(bp->mass), &(bp->colour));
		traverse(bp);
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
		j = i+b->path.pos;
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

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Usage: %s numbodies\n",argv[0]);
		return 1;
	}
	bodies = atoi(argv[1]);

	init();

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_ALPHA);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("Yay physics");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor (0.0,0.0,0.0,1.0);

	glutDisplayFunc(display);
	glutTimerFunc(TIMERMSECS, timerFunc, 0);
	glutKeyboardFunc(keyPressed);
	glutReshapeFunc(reshape);

	glutMainLoop();
}
