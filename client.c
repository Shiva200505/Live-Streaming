#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BROADCAST_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in recv_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(recv_addr);

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define receiver address
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(BROADCAST_PORT);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("======== Announcement Receiver ========\n");
    printf("Listening for announcements on port %d...\n", BROADCAST_PORT);

    // Receive the broadcast message in a loop
    while (1) {
        int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&recv_addr, &addr_len);
        if (recv_len < 0) {
            perror("Receiving failed");
            break;
        }

        buffer[recv_len] = '\0'; // Null-terminate the received message
        printf("\n>>> Received Announcement: %s\n", buffer);

        // If the message is "STOP", exit the loop
        if (strcmp(buffer, "STOP") == 0) {
            printf("\n>>> Received STOP signal. Exiting...\n");
            break;
        }

        printf("========================================\n");
    }

    // Close the socket
    close(sockfd);
    printf("Receiver socket closed. Exiting...\n");

    return 0;
}