#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <first_port> <last_port> <ip_address>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int first_port = atoi(argv[1]);
    int last_port = atoi(argv[2]);
    if ((first_port < 0)|| (last_port < 0) || (first_port > last_port)) {
        printf("Incorrect format for the program\n");
        printf("Usage: %s <first_port> <last_port> <ip_address>\n", argv[0]);
        printf("first port and last port should be greater than 0\nFirst port cannot be greater than last port\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in target_address;

    memset(&target_address, 0, sizeof(target_address));
    target_address.sin_family = AF_INET;
    if (inet_pton(AF_INET, argv[3], &target_address.sin_addr) != 1) {
        perror("inet_pton failure\n");
        exit(EXIT_FAILURE);
    }


    struct timeval timeout = {1, 0};;

    printf("Scanning the port %d through %d on the device %s", first_port, last_port, inet_ntoa(target_address.sin_addr));
    
    for (first_port; first_port <= last_port; first_port++) {

        int sockfd;
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
            continue;

        setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

        target_address.sin_port = htons(first_port);

        if ((connect(sockfd, (struct sockaddr *) &target_address, sizeof(struct sockaddr))) == 0) {
            printf("%d | open\n", first_port);
            close(sockfd);
        }
        else {
            printf("%d | closed\n", first_port);
            close(sockfd);
        }
    }
    return EXIT_SUCCESS;
    

}
