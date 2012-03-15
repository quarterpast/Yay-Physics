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

	double r;
	Body *finalBody = allBodies + bodyTotal;
	for(; allBodies != finalBody; ++allBodies) {
		if (allBodies == currentBody) continue;
		r = distance (&(currentBody->position), &(allBodies->position));
		if (r < (currentBody->radius + allBodies->radius)) {

			double combinedMass = currentBody->mass + allBodies->mass;

			Vector unitnormal = vminus (&(currentBody->position), &(allBodies->position));
			unitnormal = unit (&unitnormal);
			Vector reposition;
			reposition = smult (currentBody->radius + allBodies->radius - r, &unitnormal);
			Vector temp1, temp2;
			temp1 = smult (allBodies->mass / combinedMass, &reposition);
			temp2 = smult (currentBody->mass / combinedMass, &reposition);
			currentBody->position = vplus (&(currentBody->position), &temp1);
			allBodies->position = vminus (&(allBodies->position), &temp2);

			Vector v1n, v1t, v2n, v2t;
			v1n = smult (dot (&(currentBody->velocity), &unitnormal), &unitnormal);
			v2n = smult (dot (&(allBodies->velocity), &unitnormal), &unitnormal);
			v1t = vminus (&(currentBody->velocity), &v1n);
			v2t = vminus (&(allBodies->velocity), &v2n);

			double v1nlength = norm (&v1n);
			double v2nlength = norm (&v2n);

			double v1mult = ((currentBody->mass - allBodies->mass) / combinedMass * v1nlength) + (2 * allBodies->mass / combinedMass * v2nlength);
			double v2mult = ((allBodies->mass - currentBody->mass) / combinedMass * v2nlength) + (2 * currentBody->mass / combinedMass * v1nlength);

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
