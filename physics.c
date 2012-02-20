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
	Vector out = {(a->x)/n,(a->y)/n};
	return out;
}
Vector move(Body* thing, Body* rest, int l) {
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
		m = smult(n,&u);
		ds = vplus(&ds,&m);
	}
	vprint(&ds,"mv ");
	return ds;
}

int main(int argc, char **argv) {
	int i,j;
	Vector ds[3] = {
		{0,0},
		{0,0},
		{0,0}
	};
	Body b[3] = {
		{{0,0},{0,0},1},
		{{1,1},{0,0},2},
		{{-1,0},{0,0},3}
	};
	for(i = 0; i<1000; ++i) {
		for(j = 0; j<3; ++j) {
			ds[j] = move(&(b[j]),b,3);
			vprint(&(ds[j]),"ds ");
		}
		for(j = 0; j<3; ++j) {
			b[j].position = vplus(&(b[j].position),&ds[j]);
		}
		print(&(b[0].position),"");
	}
}