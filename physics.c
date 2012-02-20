#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define G 1e-4

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

void circle(double x, double y, double r) {
	double t;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for(t = 0; t < M_PI; t += M_PI/72) {
		glVertex2f(x + sin(t) * r, y + cos(t) * r);
	}
	glEnd();
}

void reshape (int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display() {
	glClearColor(0,0,0,1);
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	for(j = 0; j<3; ++j) {
		b[j].acceleration = move(&(b[j]),b,3,j);
	}
	for(j = 0; j<3; ++j) {
		b[j].velocity = vplus(&(b[j].velocity),&(b[j].acceleration));
		b[j].position = vplus(&(b[j].position),&(b[j].velocity));
	}
	glFlush();
}

int main(int argc, char **argv) {
	int i,j;

	Body b[3] = {
		{{0,0},{0,0},{0,0},1},
		{{1,1},{0,0},{0,0},2},
		{{-1,0},{0,0},{0,0},3}
	};

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Yay physics");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}