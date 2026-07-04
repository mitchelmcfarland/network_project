#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
    int sockfd;
    struct sockaddr_in my_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8080);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

	bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);
	
	listen(sockfd, 5);

	struct sockaddr_in client_addr;
	socklen_t addr_size;
	int client_fd;

	addr_size = sizeof client_addr;

	client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);

	printf("Connection established!\n");

	close(client_fd);

	close(sockfd);
}