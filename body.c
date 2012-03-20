#include "body.h"

Body newBody (Vector pos, Vector vel, double mass) {

	Vector *arr = malloc (PATHLEN * sizeof (Vector));
	int i;
	for (i = 0; i < PATHLEN; i++) {
		arr[i] = pos;
	}
	Path path = {
		arr,
		0
	};
	double radius = sqrt (mass) / 100;
	double gmass = G * mass;
	Body out = {
		pos,
		vel,
		{0, 0, 0},
		mass,
		gmass,
		radius,
		path,
		bodyColour ()
	};
	return out;
}

double newt (double m, double r) {

	return G * m / (r * r);
}

Vector calculateAcceleration (Body* currentBody, Body* allBodies, int bodyTotal) {

	double n, r, rsquare;
	Vector out = {0, 0, 0};
	Vector tempv;
	Body *finalBody = allBodies + bodyTotal;
	for(; allBodies != finalBody; ++allBodies) {
		if (allBodies == currentBody) continue;
		tempv = vminus (&(allBodies->position), &(currentBody->position));
		rsquare = tempv.x * tempv.x + tempv.y * tempv.y + tempv.z * tempv.z;
		n = allBodies->gmass / rsquare;
		r = sqrt (rsquare);
		tempv = smult (n / r, &tempv);
		out = vplus (&out, &tempv);
	}
	return out;
}

void collisionTest (Body* currentBody, Body* allBodies, int bodyTotal) {

	double r, rsquare, radiusSum, combinedMass, v1nlength, v2nlength, v1mult, v2mult, body1proportion, body2proportion;
	Vector unitnormal, reposition, temp1, temp2, v1n, v1t, v2n, v2t;
	Body *finalBody = allBodies + bodyTotal;
	for(; allBodies != finalBody; ++allBodies) {
		if (allBodies == currentBody) continue;
		unitnormal = vminus (&(currentBody->position), &(allBodies->position));
		rsquare = unitnormal.x * unitnormal.x + unitnormal.y * unitnormal.y + unitnormal.z * unitnormal.z;
		r = sqrt (rsquare);
		radiusSum = currentBody->radius + allBodies->radius;
		if (r < radiusSum) {
			combinedMass = currentBody->mass + allBodies->mass;
			unitnormal = unit (&unitnormal);
			body1proportion = allBodies->mass / combinedMass;
			body2proportion = currentBody->mass / combinedMass;
			reposition = smult (radiusSum - r, &unitnormal);
			temp1 = smult (body1proportion, &reposition);
			temp2 = smult (body2proportion, &reposition);
			currentBody->position = vplus (&(currentBody->position), &temp1);
			allBodies->position = vminus (&(allBodies->position), &temp2);
			v1nlength = dot (&(currentBody->velocity), &unitnormal);
			v2nlength = dot (&(allBodies->velocity), &unitnormal);
			v1n = smult (v1nlength, &unitnormal);
			v2n = smult (v2nlength, &unitnormal);
			v1t = vminus (&(currentBody->velocity), &v1n);
			v2t = vminus (&(allBodies->velocity), &v2n);
			v1nlength = fabs (v1nlength);
			v2nlength = fabs (v2nlength);
			v1mult = ((currentBody->mass - allBodies->mass) / combinedMass * v1nlength) + (2 * body1proportion * v2nlength);
			v2mult = ((allBodies->mass - currentBody->mass) / combinedMass * v2nlength) + (2 * body2proportion * v1nlength);
			temp1 = smult (v1mult, &unitnormal);
			temp2 = smult (v2mult, &unitnormal);
			currentBody->velocity = vplus (&v1t, &temp1);
			allBodies->velocity = vminus (&v2t, &temp2);
		}
	}
}

Vector bodyColour (void) {

	static const double rep = 2.0 * RAND_MAX;
	double r = 1.0 - rand () / rep;
	double g = 1.0 - rand () / rep;
	double b = 1.0 - rand () / rep;
	Vector out = {r, g, b};
	return out;
}
