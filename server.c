#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BROADCAST_PORT 8080
#define BROADCAST_IP "255.255.255.255"
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in broadcast_addr;
    int broadcast_permission = 1;
    char message[BUFFER_SIZE];

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to allow broadcast
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_permission, sizeof(broadcast_permission)) < 0) {
        perror("Error setting socket options for broadcast");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Define broadcast address
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(BROADCAST_PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

    printf("======== Broadcast Announcement System ========\n");

    // Enter loop to send messages
    while (1) {
        printf("\nEnter the announcement message (type 'STOP' to end): ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0;  // Remove newline character from input

        // Send the announcement as a broadcast
        if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            perror("Broadcast failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        printf("\n>>> Announcement Sent: %s\n", message);

        // If the message is "STOP", exit the loop
        if (strcmp(message, "STOP") == 0) {
            printf("\n>>> Broadcast Stopped <<<\n");
            break;
        }

        printf("=================================================\n");
    }

    // Close the socket
    close(sockfd);
    printf("Server socket closed. Exiting...\n");

    return 0;
}