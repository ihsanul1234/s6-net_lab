#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024] = {0};
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    // Configure server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address / Address not supported.\n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed\n");
        return -1;
    }

    // Send and receive messages
    while (1) {
        printf("from client(type your msg): ");
        fgets(hello, 1024, stdin);
        hello[strcspn(hello, "\n")] = '\0'; // Remove newline character

        // Exit if user types "exit"
        if (strcmp(hello, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }

        // Send message to server
        if (send(sock, hello, strlen(hello), 0) < 0) {
            perror("send failed");
            break;
        }

        // Receive response from server
        valread = read(sock, buffer, 1024);
        if (valread < 0) {
            perror("read failed");
            break;
        } else if (valread == 0) {
            printf("Server disconnected.\n");
            break;
        }

        // Print server's response
        buffer[valread] = '\0'; // Null-terminate the buffer
        printf("Server: %s\n", buffer);
    }

    close(sock);
    return 0;
}
