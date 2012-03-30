#include "serialiser.h"

#include "string.h"

NetworkBody bodyToNetworkBody(Body *b) {
	NetworkBody ret;
	ret.position = b->position;
	ret.velocity = b->velocity;
	ret.mass = b->mass;
	ret.colour = b->colour;
	return ret;
}

void networkBodyToByteArray(NetworkBody *b, char *s) {
	memcpy((void *)s, (void *)b, sizeof(NetworkBody));
}

void byteArrayToNetworkBody(char *s, NetworkBody *b) {
	memcpy((void *)b, (void *)s, sizeof(NetworkBody));
}
