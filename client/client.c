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
    int status;
    
    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8080);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

    if (status = connect(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr) < 0) {
        perror("connection failed\n");
        return -1;
    }

    printf("we are connected!\n");

    close(sockfd);
}
