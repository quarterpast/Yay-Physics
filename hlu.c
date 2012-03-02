#include "hlu.h"

Hlu newHlu (Vector heading, Vector left, Vector up) {

	Hlu out = {heading, left, up};
	return out;
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
