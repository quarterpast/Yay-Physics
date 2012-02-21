#ifndef PATH_H
#define PATH_H 1

typedef struct {
	Vector *point;
	size_t pos;
} Path;

void startPath(Body*);
void drawPath(Body*,Vector*,int);
void endPath(Body*);
void traverse(Body*,void (*start)(Body*),void (*cb)(Body*,Vector*,int),void (*end)(Body*));

#endif