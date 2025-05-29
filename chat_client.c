#include <stdio.h> // printf(), perror()
#include <stdlib.h> // exit(), atoi()
#include <string.h> // memset()
#include <unistd.h> // read(), write(), close()
#include <arpa/inet.h> // inet_addr(), sockaddr_in()
#include <sys/socket.h> // socket(), bind(), listen(), accept()

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){

    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 1. Create a TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Connect to local host

    // 3. Connect to the server
    if(connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server!\n");

    // 4. Chat loop
    while(1){
        // Get user message
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        write(sock, buffer, strlen(buffer));

        // Get server response
        memset(buffer, 0, BUFFER_SIZE);
        int bytes = read(sock, buffer, BUFFER_SIZE);
        if(bytes <= 0){
            printf("Server disconnected.\n");
            break;
        }
        printf("Server: %s", buffer);
    }

    // 5. Close socket
    close(sock);

    return 0;
}