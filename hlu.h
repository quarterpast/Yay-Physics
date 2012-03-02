#ifndef HLU_H
#define HLU_H

#include <math.h>
#include "vector.h"

#define TURN_ANGLE 0.01
#define CTHETA (cos (TURN_ANGLE))
#define STHETA (sin (TURN_ANGLE))

typedef struct {
	Vector heading;
	Vector left;
	Vector up;
} Hlu;

Hlu newHlu (Vector, Vector, Vector);
void pitchUp (Hlu *);
void pitchDown (Hlu *);
void rollLeft (Hlu *);
void rollRight (Hlu *);
void yawLeft (Hlu *);
void yawRight (Hlu *);

#endif
