#ifndef HLU_H
#define HLU_H

#include "vector.h"

typedef struct {
	Vector heading;
	Vector left;
	Vector up;
} Hlu;

Hlu newHlu (Vector *heading, Vector *left, Vector *up);
void pitchUp (Hlu *);
void pitchDown (Hlu *);
void rollLeft (Hlu *);
void rollRight (Hlu *);
void yawLeft (Hlu *);
void yawRight (Hlu *);

#endif // HLU_H
