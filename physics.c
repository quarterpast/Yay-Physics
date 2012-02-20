#include <stdio.h>
#include <math.h>
#define G 1e-4

typedef struct {
	double x;
	double y;
} Vector;

typedef struct {
	Vector position;
	Vector initial;
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
void print(Vector *a) {
	printf("(%f,%f)\n",a->x,a->y);
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
	Vector out = {(a->x)/n,(a->y)/n};
	return out;
}
void move(Body* thing, Body* rest, int l) {
	int i;
	double n, r;
	Vector ds = {0,0}, diff, u ,m;
	Body b;
	for(i=0; i<l; ++i) {
		b = rest[i];
		r = distance(&(thing->position),&(b.position));
		n = newt(rest[i].mass,r);
		diff = vminus(&(b.position),&(thing->position));
		u = unit(&diff);
		m = smult(l,&u);
		ds = vplus(&ds,&m);
	}
	thing->position = vplus(&(thing->position),&ds);
}

int main(int argc, char **argv) {
	int i;
	Body a = {{0,0},{0,0},1};
	Body other[2] = {
		{{1,1},{0,0},2},
		{{-1,0},{0,0},3}
	};
	for(i = 0; i<100000; ++i) {
		move(&a,other,2);
		printf("%f %f\n",a.x,a.y);
	}
}