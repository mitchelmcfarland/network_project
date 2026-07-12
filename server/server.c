#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_MESSAGE_LEN 4096

int main () {
	//int yes = 1;
    int sockfd;
    struct sockaddr_in my_addr;
	char buffer[MAX_MESSAGE_LEN];
    
    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8080);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

	bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);

	printf("Waiting for connection...\n");
	
	listen(sockfd, 5);

	struct sockaddr_in client_addr;
	socklen_t addr_size;
	int client_fd;

	addr_size = sizeof client_addr;

	client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);

	printf("Connection established!\nYou are now chatting. Type '/exit' to quit.\n");

	while(1) {
		char *buff_pointer;

		printf("> ");

		buff_pointer = fgets(buffer, MAX_MESSAGE_LEN, stdin);

		//buffer[strcspn(buffer, "\n") = '\0'];

		if (strncmp(buffer, "/exit", 5) == 0 || buff_pointer == NULL) {
			printf("Exiting program...\n");
			break;
		}

		send(client_fd, buffer, MAX_MESSAGE_LEN, 0);

		printf("Message sent.\n");

	}
	
	close(client_fd);

	close(sockfd);

	return 0;
}