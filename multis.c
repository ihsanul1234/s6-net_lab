#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <asm-generic/socket.h>
#define PORT 8080

int main(int argc, char const* argv[]) 
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char hello[1024];
    pid_t childpid;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed.");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) 
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept connections
    for (;;) 
    {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) 
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Fork a child process
        if ((childpid = fork()) == 0) 
        {
            close(server_fd); // Child doesn't need the listener

            // Handle client communication
            while ((valread = read(new_socket, buffer, 1024)) > 0) 
            {
                printf("Client: %s\n", buffer);
                printf("Msg to client: ");
                scanf("%s", hello);
                send(new_socket, hello, strlen(hello), 0);
                memset(buffer, 0, sizeof(buffer)); // Clear buffer
            }

            if (valread == 0) 
            {
                printf("Client disconnected.\n");
            } 
            else 
            {
                perror("read");
            }

            close(new_socket);
            exit(EXIT_SUCCESS); // Exit child process
        }

        close(new_socket); // Parent closes client socket
    }

    return 0;
}
