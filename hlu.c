#include "hlu.h"

#include <math.h>

#define TURN_ANGLE 0.02
#define CTHETA (cos (TURN_ANGLE))
#define STHETA (sin (TURN_ANGLE))

Hlu newHlu (Vector *heading, Vector *left, Vector *up) {

	return (Hlu){*heading, *left, *up};
}

void pitchUp (Hlu *c) {

	Vector temp, temp1, temp2;
	temp1 = smult (CTHETA, &(c->heading));
	temp2 = smult (STHETA, &(c->up));
	temp = vplus (&temp1, &temp2);
	temp1 = smult (STHETA, &(c->heading));
	temp2 = smult (CTHETA, &(c->up));
	c->up = vminus (&temp2, &temp1);
	c->heading = temp;
}

void pitchDown (Hlu *c) {

	Vector temp, temp1, temp2;
	temp1 = smult (CTHETA, &(c->heading));
	temp2 = smult (STHETA, &(c->up));
	temp = vminus (&temp1, &temp2);
	temp1 = smult (STHETA, &(c->heading));
	temp2 = smult (CTHETA, &(c->up));
	c->up = vplus (&temp2, &temp1);
	c->heading = temp;
}

void rollLeft (Hlu *c) {

	Vector temp, temp1, temp2;
	temp1 = smult (CTHETA, &(c->left));
	temp2 = smult (STHETA, &(c->up));
	temp = vminus (&temp1, &temp2);
	temp1 = smult (STHETA, &(c->left));
	temp2 = smult (CTHETA, &(c->up));
	c->up = vplus (&temp1, &temp2);
	c->left = temp;
}

void rollRight (Hlu *c) {

	Vector temp, temp1, temp2;
	temp1 = smult (CTHETA, &(c->left));
	temp2 = smult (STHETA, &(c->up));
	temp = vplus (&temp1, &temp2);
	temp1 = smult (STHETA, &(c->left));
	temp2 = smult (CTHETA, &(c->up));
	c->up = vminus (&temp2, &temp1);
	c->left = temp;
}

void yawLeft (Hlu *c) {

	Vector temp, temp1, temp2;
	temp1 = smult (CTHETA, &(c->heading));
	temp2 = smult (STHETA, &(c->left));
	temp = vplus (&temp1, &temp2);
	temp1 = smult (STHETA, &(c->heading));
	temp2 = smult (CTHETA, &(c->left));
	c->left = vminus (&temp2, &temp1);
	c->heading = temp;
}

void yawRight (Hlu *c) {

	Vector temp, temp1, temp2;
	temp1 = smult (CTHETA, &(c->heading));
	temp2 = smult (STHETA, &(c->left));
	temp = vminus (&temp1, &temp2);
	temp1 = smult (STHETA, &(c->heading));
	temp2 = smult (CTHETA, &(c->left));
	c->left = vplus (&temp1, &temp2);
	c->heading = temp;
}
