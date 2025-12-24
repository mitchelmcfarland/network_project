#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main () {
	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo;

	memset(&hints, 0, sizeof hints);
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	if ((status = getaddrinfo(NULL, "3500", &hints, &servinfo)) != 0) {
		fprintf(stderr, "Gai error: %s\n", gai_strerror(status));
		exit(1);
	}

	char ip_address[INET_ADDRSTRLEN];

	struct addrinfo *p;

	for (p = servinfo; p != NULL; p = p->ai_next) {
		
		struct sockaddr_in *ipv4;
		
		ipv4 = (struct sockaddr_in *)p->ai_addr;

		inet_ntop(AF_INET, &(ipv4->sin_addr), ip_address, INET_ADDRSTRLEN);

		printf("%s\n", ip_address);
	}

	freeaddrinfo(servinfo);
}
