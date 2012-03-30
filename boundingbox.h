#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "vector.h"

// position is bottom left
typedef struct {
	Vector position;
	Vector size;
} BoundingBox;

#endif /* BOUNDINGBOX_H */
