#include "physics.h"
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