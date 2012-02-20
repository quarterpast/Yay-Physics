#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define G 1e-8
#define WIDTH 750
#define HEIGHT 750
#define TIMERMSECS 1000/60
#define PATHLEN 1024

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
	r = fmax(r,2);
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
		// glutLeaveFullScreen();
	}
}

void reshape (int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
void startPath(Body *b) {
	glBegin(GL_LINE_STRIP);
}
void drawPath(Body *b,Vector *pos) {
	Vector px = coordToScreen(pos);
	glVertex2f(px.x,px.y);
}
void endPath(Body *b) {
	glEnd();
}

void traverse(
	Body *b,
	void (*start)(Body*),
	void (*cb)(Body*,Vector*),
	void (*end)(Body*)
) {
	int i,j;
	start(b);
	for(i = 0; i<PATHLEN; ++i) {
		j = i+b->path.pos;
		if(j > PATHLEN) {
			j -= PATHLEN;
		}
		cb(b,&(b->path.point[j]));
	}
	end(b);
}

Body newBody(Vector pos, Vector vel, double mass) {
	Vector *arr = malloc(PATHLEN*sizeof(Vector));
	arr[0] = pos;
	int i;
	Path path = {
		arr,
		0
	};
	Body out = {
		pos,
		vel,
		{0,0},
		mass,
		path
	};

	return out;
}
Vector newVector(double x, double y) {
	Vector out = {x,y};
	return out;
}


Body b[4] = {};

static const int bodies = 4;

void step() {
	int j;
	glutTimerFunc(TIMERMSECS, step, 0);

	glClearColor(0,0,0,1);
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	for(j = 0; j<bodies; ++j) {
		b[j].acceleration = move(&(b[j]),b,bodies,j);
	}
	for(j = 0; j<bodies; ++j) {
		b[j].velocity = vplus(&(b[j].velocity),&(b[j].acceleration));
		b[j].position = vplus(&(b[j].position),&(b[j].velocity));
		if(b[j].path.pos >= PATHLEN) {
			b[j].path.pos = b[j].path.pos + 1 - PATHLEN;
		}
		else {
			b[j].path.pos++;
		}
		b[j].path.point[b[j].path.pos] = b[j].position;
		circle(&(b[j].position),sqrt(b[j].mass));
		traverse(&(b[j]),startPath,drawPath,endPath);
	}
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE);
	glutInitWindowSize (WIDTH, HEIGHT);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("Yay physics");


	b[0] = newBody(newVector(0,0.00001),newVector(0,0),100);
	b[1] = newBody(newVector(1,0),newVector(0,0.001),1);
	b[2] = newBody(newVector(-0.7,0),newVector(0,0.0005),1);
	b[3] = newBody(newVector(0,0.5),newVector(0.001,0.001),1);

	//glutDisplayFunc(display);
	glutTimerFunc(TIMERMSECS, step, 0);
	glutKeyboardFunc(keyPressed);
	glutReshapeFunc(reshape);

	glutMainLoop();
}