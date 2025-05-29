#include <stdio.h> // printf(), perror(), fgets()
#include <stdlib.h> // exit()
#include <string.h> // memset()
#include <unistd.h> // read(), write(), close()
#include <arpa/inet.h> // htons(), inet_addr(), sockaddr_in
#include <sys/socket.h> // socket(), bind(), listen(), accept(), connect()

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){

    int server_fd; // Server's listening socket
    int client_socket; // Socket used to communicate with a connected client
    struct sockaddr_in server_addr, client_addr; // Store info like IP addresses and port
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // 1. Create a TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. Configure server address (IPV4 + port)
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on any local IP
    server_addr.sin_port = htons(PORT);

    // 3. Bind the socket to the IP/Port
    if(bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. Start listening for connections
    if(listen(server_fd, 1) < 0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);
    
    // 5. Accept a client connection
    client_socket = accept(server_fd, (struct sockaddr*) &client_addr, &addr_len);
    if(client_socket < 0){ // client_socket can be used for communication with that specific client
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");
    
    // 6. Chat loop
    while(1){
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_recieved = read(client_socket, buffer, BUFFER_SIZE);
        if(bytes_recieved <= 0){
            printf("Client disconnected.\n");
            break;
        }

        printf("Client: %s", buffer);// Show message on the server side

        // Send the message back (echo)
        send(client_socket, buffer, bytes_recieved, 0);
    }

    // 7. Close the sockets
    close(client_socket);
    close(server_fd);

    return 0;
}

