#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LENGTH 4096

int main () {
    int sockfd;
    struct sockaddr_in my_addr;
    int status;
    char buffer[MAX_LENGTH];
    
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

    printf("Connection established.\n");

    while (1) {
        int conn;

        conn = recv(sockfd, buffer, MAX_LENGTH, 0);

        if (conn == 0) {
            printf("Lost connection to the host.\n");
            break;
        }
        
        printf("%s", buffer);
    }

    close(sockfd);
}
