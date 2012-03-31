#include "serialiser.h"

#include "string.h"

static const double tol = 1.0e-4;

NetworkBody bodyToNetworkBody(Body *b, BoundingBox *box) {
	NetworkBody ret;

	ret.position = vminus(&b->position, &box->position);
	ret.position.x /= box->size.x;
	ret.position.y /= box->size.y;

	ret.velocity = b->velocity;
	ret.mass = b->mass;
	ret.colour = b->colour;

	return ret;
}

Body networkBodyToBody(NetworkBody *b, BoundingBox *box) {
	Body ret;

	ret.position = b->position;
	ret.position.x *= box->size.x;
	ret.position.y *= box->size.y;
	ret.position = vadd(&ret.position, &box->position);

	ret.velocity = b->velocity;
	ret.mass = b->mass;
	ret.colour = b->colour;
	
	return ret;
}

void torusTransformNetowrkBody(NetworkBody *b) {
	if (b->position.x >= 1.0)
		b->position.x = 0.0 + tol;
	else if (b->position.x <= 0.0)
		b->position.x = 1.0 - tol;
	if (b->position.y >= 1.0)
		b->position.y = 0.0 + tol;
	else if (b->position.y <= 0.0)
		b->position.y = 1.0 - tol;
}

void networkBodyToByteArray(NetworkBody *b, char *s) {
	memcpy((void *)s, (void *)b, sizeof(NetworkBody));
}

void byteArrayToNetworkBody(char *s, NetworkBody *b) {
	memcpy((void *)b, (void *)s, sizeof(NetworkBody));
}
