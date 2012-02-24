#include "unitcircle.h"

#include <stdlib.h>
#include <math.h>
#include "openglincludes.h"

#include "vector.h"
#include "colour.h"
#include "physics.h"

Vector * generateUnitCircle(size_t numVertices) {
	Vector *circle = (Vector *)malloc(sizeof(Vector) * numVertices);
	double a = 0.0;
	double del = 2.0 * M_PI / (double)numVertices;
	int i;

	for (i = 0; i < numVertices; ++i, a += del) {
		circle[i].x = sin(a);
		circle[i].y = cos(a);
	}

	return circle;
}
