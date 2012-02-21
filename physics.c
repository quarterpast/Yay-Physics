#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#define G 1e-8
#define WIDTH 750
#define HEIGHT 750
#define TIMERMSECS 1000/60
#define STEP 1.2
#define PATHLEN 1
#define PATH_MOD(t) {if(t>=PATHLEN) t-=PATHLEN;}

typedef struct {
	double r;
	double g;
	double b;
	double a;
} Colour;

typedef struct {
	double x;
	double y;
} Vector;

typedef struct {
	Vector *point;
	size_t pos;
} Path;

typedef struct {
	Vector position;
	Vector velocity;
	Vector acceleration;
	double mass;
	Path path;
	Colour colour;
} Body;

Body *b;
int bodies;
double steps = 2.0;
int width = WIDTH;
int height = HEIGHT;

void glColour(Colour*);
Colour randColour();

Vector newVector(double, double); /* toil and trouble */
Vector vplus(Vector*, Vector*);
Vector vminus(Vector*, Vector*);
Vector smult(double, Vector*);
double norm(Vector *);
double distance(Vector*, Vector*);
Vector unit(Vector*);
Vector coordToScreen(Vector*);

void startPath(Body*);
void drawPath(Body*,Vector*,int);
void endPath(Body*);
void traverse(Body*,void (*)(Body*),void (*)(Body*,Vector*,int),void (*)(Body*));

Body newBody(Vector, Vector, double);
double newt(double, double);
bool collide(Body*, Body*, int, int);
Vector move(Body*, Body*, int, int);
void circle(Vector*, double, Colour*);

void keyPressed(unsigned char, int, int);
void reshape(int, int);
void step();

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_ALPHA);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("Yay physics");

	srand(time(NULL));
	if(argc < 2) return 1;

	bodies = atoi(argv[1]);
	b = malloc(bodies*sizeof(Body));
	int i;
	//b[0] = newBody(newVector(0,0.0001),newVector(0,0),1000);
	for(i=0;i<bodies;++i) {
		b[i] = newBody(newVector(
			1-2*(float)rand()/(float)RAND_MAX,
			1-2*(float)rand()/(float)RAND_MAX
		),
		newVector(
			0.002-0.004*(float)rand()/(float)RAND_MAX,
			0.002-0.004*(float)rand()/(float)RAND_MAX
		),100*(float)rand()/(float)RAND_MAX);
	}

	glutDisplayFunc(step);
	glutTimerFunc(TIMERMSECS, step, 0);
	glutKeyboardFunc(keyPressed);
	glutReshapeFunc(reshape);

	glutMainLoop();
}
/*
Colour fadey functions
*/
void glColour(Colour *c) {
	glColor4f(c->r,c->g,c->b,c->a);
}
Colour fade(Colour *c,int i) {
	Colour out = {
		c->r,
		c->g,
		c->b,
		c->a*(double)i/(double)PATHLEN
	};
	return out;
}
Colour randColour() {
	double r = 1-0.5*(double)rand()/(double)RAND_MAX,
	g = 1-0.5*(double)rand()/(double)RAND_MAX,
	b = 1-0.5*(double)rand()/(double)RAND_MAX,
	a = 1;
	Colour out = {r,g,b,a};
	return out;
}
/*
Vectors!
*/

Vector newVector(double x, double y) {
	Vector out = {x,y};
	return out;
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
Vector coordToScreen(Vector *pos) {
	Vector out = {pos->x*WIDTH/width,pos->y*HEIGHT/height};
	return out;
}

/* Path (for the trails) */

void startPath(Body *b) {
	glBegin(GL_LINE_STRIP);
}
void drawPath(Body *b,Vector *pos,int i) {
	Vector px = coordToScreen(pos);
	Colour faded = fade(&(b->colour),i);
	glColour(&faded);
	glVertex2f(px.x,px.y);
}
void endPath(Body *b) {
	glEnd();
}
void traverse(
	Body *b,
	void (*start)(Body*),
	void (*cb)(Body*,Vector*,int),
	void (*end)(Body*)
) {
	int i,j;
	start(b);
	for(i = 1; i<PATHLEN; i++) {
		j = i+b->path.pos;
		PATH_MOD(j);
		cb(b,&(b->path.point[j]),i);
	}
	end(b);
}

/* Body */
Body newBody(Vector pos, Vector vel, double mass) {
	Vector *arr = malloc(PATHLEN*sizeof(Vector));
	int i;
	for(i = 0; i<PATHLEN; i++) {
		arr[i] = pos;
	}
	Path path = {
		arr,
		0
	};
	Body out = {
		pos,
		vel,
		{0,0},
		mass,
		path,
		randColour()
	};

	return out;
}
double newt(double m, double r) {
	return G*m/(r*r);
}
bool collide(Body *thing, Body *rest, int l, int skip) {
	int i;
	double n, r;
	Vector ds = {0,0}, diff, u ,m;
	Body b;
	for(i=0; i<l; ++i) {
		if(i == skip) continue;
		b = rest[i];
		r = distance(&(thing->position),&(b.position));
		printf("%f %f\n",r, sqrt(thing->mass)+sqrt(b.mass));
		if(r < sqrt(thing->mass)+sqrt(b.mass)) return true;
	}
	return false;
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
void circle(Vector *pos, double r, Colour *c) {
	double t;
	Vector sc = coordToScreen(pos);
	glBegin(GL_TRIANGLE_FAN);
	glColour(c);
	glVertex2f(sc.x,sc.y);
	r = fmax(r,2);
	for(t = 0; t < M_PI*2; t += M_PI/72) {
		glVertex2f(sc.x+sin(t)*r/width, sc.y+cos(t)*r/height);
	}
	glEnd();
}

/* GL/GLUT stuff */
void keyPressed (unsigned char key, int x, int y) {
	printf("%c\n",key);
	if(key == 'f') {
		//glutFullScreenToggle();
	}
	if(key == 'q') {
		//glutLeaveMainLoop();
	}
	if(key == '+') {
		steps *= STEP;
	}
	if(key == '-') {
		steps /= STEP;
		if(steps <= 1) steps = 1;
	}
	if(key == '\x1e') {
		// glutLeaveFullScreen();
	}
}
void reshape (int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
void step() {
	int j,k;
	Colour red = {1.0,0.0,0.0,1.0};
	glutTimerFunc(TIMERMSECS, step, 0);

	glClear (GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,1);
	glLoadIdentity();

	for(k = 0; k<(int)steps; k++) {
		for(j = 0; j<bodies; ++j) {
			b[j].acceleration = move(&(b[j]),b,bodies,j);
		}
		for(j = 0; j<bodies; ++j) {
			b[j].velocity = vplus(&(b[j].velocity),&(b[j].acceleration));
			b[j].position = vplus(&(b[j].position),&(b[j].velocity));
			b[j].path.pos++;
			PATH_MOD(b[j].path.pos);
			b[j].path.point[b[j].path.pos] = b[j].position;
		}
	}
	for(j = 0; j<bodies; ++j) {
		if(collide(&(b[j]),b,bodies,j)) b[j].colour = red;
		circle(&(b[j].position),sqrt(b[j].mass),&(b[j].colour));
		traverse(&(b[j]),startPath,drawPath,endPath);
	}
	glutSwapBuffers();
}