#include "physics.h"
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