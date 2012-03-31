#ifndef SERIALISER_H
#define SERIALISER_H

#include <sys/types.h>

#include "vector.h"
#include "colour.h"
#include "body.h"
#include "boundingbox.h"

typedef struct {
	Vector position;
	Vector velocity;
	double mass;
	Colour colour;
} NetworkBody;

NetworkBody bodyToNetworkBody(Body *b, BoundingBox *box);
Body networkBodyToBody(NetworkBody *b, BoundingBox *box);
void torusTransformNetowrkBody(NetworkBody *b);
void networkBodyToByteArray(NetworkBody *b, char *s);
void byteArrayToNetworkBody(char *s, NetworkBody *b);

#endif /* SERIALISER_H */
