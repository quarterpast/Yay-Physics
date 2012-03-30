#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>

#include "serialiser.h"

int *clientSocketFds;
int maxNumClients = 4;
int numClients;

struct sockaddr_storage 	 clientAddr;
socklen_t					 clientAddrLen;
int							 localPortSocketFd;

pthread_t acceptThread;
pthread_t *redirectThreads;
int *threadIndices;

void * redirectMessages(void *data)
{
	size_t bufferLen = 2 * sizeof(SerialisedBody);
	char buffer[bufferLen];
	int messageLen;
	int i;
	int threadNum = *((int *)data);
	NetworkBody b;

	for (;;) {
		memset(buffer, 0, bufferLen);
		messageLen = recv(clientSocketFds[threadNum], buffer, bufferLen, 0);
		if (messageLen <= 0 || messageLen > sizeof(NetworkBody))
			pthread_exit(NULL);
		byteArrayToNetworkBody(buffer, &b);
		// move position
		networkBodyToByteArray(&b, buffer);
		send(clientSocketFds[rand() % numClients], buffer, sizeof(NetworkBody), 0);
	}
}

int main(int argc, char **argv)
{
	srand(time());

	struct addrinfo 			*localhostInfo,
								 hints;
	int 						 err;
	int							 i;

	if (argc != 2) {
		exit(EXIT_FAILURE);
	}

	clientSocketFds = (int *)calloc(maxNumClients, sizeof(int));
	threadIndices = (int *)calloc(maxNumClients, sizeof(int));
	redirectThreads = (pthread_t *)calloc(maxNumClients, sizeof(pthread_t));
	numClients = 0;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	err = getaddrinfo(NULL, argv[1], &hints, &localhostInfo);
	if (err != 0) {
		fprintf(stderr, "%s\n", gai_strerror(err));
		exit(EXIT_FAILURE);
	}

	localPortSocketFd = socket(
		localhostInfo->ai_family,
		localhostInfo->ai_socktype,
		localhostInfo->ai_protocol
	);
	if (localPortSocketFd == -1) {
		fprintf(stderr, "Failed to obtain local port socket file descriptor.\n");
		exit(EXIT_FAILURE);
	}

	err = bind(
		localPortSocketFd,
		localhostInfo->ai_addr,
		localhostInfo->ai_addrlen
	);
	if (err == -1) {
		fprintf(stderr, "Failed to bind local port to file descriptor.\n");
		exit(EXIT_FAILURE);
	}

	err = listen(localPortSocketFd, maxNumClients);
	if (err == -1) {
		fprintf(stderr, "Failed to listen to local port\n");
		exit(EXIT_FAILURE);
	}

	clientAddrLen = sizeof(clientAddr);
	while (numClients < maxNumClients) {
		clientSocketFds[numClients] = accept(
			localPortSocketFd,
			(struct sockaddr *)&clientAddr,
			&clientAddrLen
		);
		if (clientSocketFds[numClients] == -1) {
			fprintf(stderr, "Failed to accept incomming connection.\n");
			continue;
		}

		threadIndices[numClients] = numClients;
		pthread_create(
			&redirectThreads[numClients],
			NULL,
			redirectMessages,
			&threadIndices[numClients]
		);

		++numClients;
	}
	
	for (i=0; i<numClients; ++i)
		close(clientSocketFds[i]);
	close(localPortSocketFd);
	free(clientSocketFds);
	free(threadIndices);
	free(redirectThreads);

	return EXIT_SUCCESS;
}
