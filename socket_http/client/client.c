#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <server_ip> <port> <file_path>\n", argv[0]);
        return 1;
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    char *file_path = argv[3];

    // Create socket
    int socket_desc;
    struct sockaddr_in server;
    char message[BUFFER_SIZE], server_reply[BUFFER_SIZE];
    FILE *file;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Connect to server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection error\n");
        return 1;
    }

    // Send HTTP GET request
    sprintf(message, "GET /%s HTTP/1.1\r\n\r\n", file_path);
    if (send(socket_desc, message, strlen(message), 0) < 0) {
        printf("Send failed\n");
        return 1;
    }

    // Receive response
    int total_bytes_received = 0;
    file = fopen("received_file", "wb");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (1) {
        int bytes_received = recv(socket_desc, server_reply, BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            printf("Receive failed\n");
            return 1;
        } else if (bytes_received == 0) {
            break; // Connection closed by server
        }

        total_bytes_received += bytes_received;
        fwrite(server_reply, 1, bytes_received, file);
    }

    printf("File received successfully. Total bytes received: %d\n", total_bytes_received);

    fclose(file);
    close(socket_desc);

    return 0;
}
