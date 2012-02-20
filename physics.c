#include <stdio.h>
#include <math.h>
#define G 1e-4

typedef struct {
	double x;
	double y;
} Vector

typedef struct {
	Vector position;
	Vector initial;
	double mass;
} Body;

double newt(double m, , double r) {
	return G*m/(r*r);
}
double d(double x1, double x2, double y1, double y2) {
	double dx = x1-x2,
	dy = y1-y2;
	return sqrt(dx*dx+dy*dy);
}
double unitx(double x1, double x2, double y1, double y2) {
	return (x2-x1)/d(x1,x2,y1,y2);
}
double unity(double x1, double x2, double y1, double y2) {
	return (y2-y1)/d(x1,x2,y1,y2);
}
void move(Body* thing, Body* rest, int l) {
	int i;
	double dx = 0,dy = 0, n, r;
	Body b;
	for(i=0; i<l; ++i) {
		b = rest[i];
		r = d(thing->x,b.x,thing->y,b.y);
		n = newt(thing->mass,rest[i].mass,r);
		dx += n*unitx(thing->x,b.x,thing->y,b.y);
		dy += n*unity(thing->x,b.x,thing->y,b.y);
	}
	thing->x += dx;
	thing->y += dy;
}

int main(int argc, char **argv) {
	int i;
	Body a = {0,0,1};
	Body other[2] = {
		{1,1,2},
		{-1,0,3}
	};
	for(i = 0; i<100000; ++i) {
		move(&a,other,2);
		printf("%f %f\n",a.x,a.y);
	}
}