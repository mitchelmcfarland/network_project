#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

#define MAX_LENGTH 4096

int main () {
    int sockfd;
    struct sockaddr_in my_addr;
    int status;
    char buffer[MAX_LENGTH];
    char exit_buf[7];
    struct pollfd pfds[2];
    
    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8080);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

    status = connect(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);
    
    if (status < 0) {
        perror("Connection failed");
        return -1;
    }

    pfds[0].fd = STDIN_FILENO;
    pfds[0].events = POLLIN;
    pfds[1].fd = sockfd;
    pfds[1].events = POLLIN;

    printf("Connection established.\n");

    while (1) {
        int conn;
        int poll_count;
        char *buff_pointer;

        poll_count = poll(pfds, 2, -1);

        if (poll_count > 0) {
            if (pfds[1].revents & POLLIN) {
                conn = recv(sockfd, buffer, MAX_LENGTH, 0);
                printf("%s", buffer);
            }

            if (pfds[0].revents & POLLIN) {
                buff_pointer = fgets(exit_buf, 7, stdin);
            }
        }

        if (strncmp(exit_buf, "/exit", 5) == 0 || buff_pointer == NULL) {
			printf("Exiting program...\n");
			break;
		}

        if (conn == 0) {
            printf("Lost connection to the host.\n");
            break;
        }
    }

    close(sockfd);
}
