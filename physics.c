#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define G 1e-7
#define WIDTH 750
#define HEIGHT 750

typedef struct {
	double x;
	double y;
} Vector;

typedef struct {
	Vector position;
	Vector velocity;
	Vector acceleration;
	double mass;
} Body;

double newt(double m, double r) {
	return G*m/(r*r);
}
Vector vplus(Vector *a, Vector *b) {
	Vector out = {a->x + b->x, a->y + b->y};
	return out;
}
Vector vminus(Vector *a, Vector *b) {
	Vector out = {a->x - b->x, a->y - b->y};
	return out;
}
Vector smult(double l, Vector *a) {
	Vector out = {(a->x)*l, (a->y)*l};
	return out;
}
void vprint(Vector *a,char *str) {
	printf("%s(%f,%f)\n",str,a->x,a->y);
}
double norm(Vector *a) {
	return sqrt(a->x * a->x + a->y * a->y);
}
double distance(Vector *a, Vector *b) {
	Vector d = vminus(a,b);
	return norm(&d);
}
Vector unit(Vector *a) {
	double n = norm(a);
	if(n == 0) {
		n = 1;
	}
	Vector out = {(a->x)/n,(a->y)/n};
	return out;
}
Vector move(Body* thing, Body* rest, int l, int skip) {
	int i;
	double n, r;
	Vector ds = {0,0}, diff, u ,m;
	Body b;
	for(i=0; i<l; ++i) {
		if(i == skip) continue;
		b = rest[i];
		r = distance(&(thing->position),&(b.position));
		n = newt(rest[i].mass,r);
		diff = vminus(&(b.position),&(thing->position));

		u = unit(&diff);
		m = smult(n,&u);
		ds = vplus(&ds,&m);
	}
	return ds;
}
int width = WIDTH;
int height = HEIGHT;

Vector coordToScreen(Vector *pos) {
	Vector out = {pos->x*WIDTH/width,pos->y*HEIGHT/height};
	return out;
}

void circle(Vector *pos, double r) {
	double t;
	Vector sc = coordToScreen(pos);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(sc.x,sc.y);
	r = fmax(r,1);
	for(t = 0; t < M_PI*2; t += M_PI/72) {
		glVertex2f(sc.x+sin(t)*r/width, sc.y+cos(t)*r/height);
	}
	glEnd();
}

void keyPressed (unsigned char key, int x, int y) {
	printf("%c\n",key);
	if(key == 'f') {
		glutFullScreenToggle();
	}
	if(key == '\x1e') {
		glutLeaveFullScreen();
	}
}

void reshape (int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

Body b[6] = {
	{{0.001,0},{0,0},{0,0},100},
	{{1,0},{0.002,0.001},{0,0},100},
	{{0,-0.5},{0.0015,0.0015},{0,0},100},
	{{-1,0},{0,-0.0015},{0,0},100},
	{{0,0.7},{0.005,0},{0,0},100},
	{{-0.5,-0.5},{0,0.0015},{0,0},100}
};
static const int bodies = 6;

void display() {
	int j;

	glClearColor(0,0,0,1);
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	for(j = 0; j<bodies; ++j) {
		b[j].acceleration = move(&(b[j]),b,3,j);
	}
	for(j = 0; j<bodies; ++j) {
		b[j].velocity = vplus(&(b[j].velocity),&(b[j].acceleration));
		b[j].position = vplus(&(b[j].position),&(b[j].velocity));
		circle(&(b[j].position),sqrt(b[j].mass));
	}
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("Yay physics");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyPressed);
	glutReshapeFunc(reshape);

	glutMainLoop();
}