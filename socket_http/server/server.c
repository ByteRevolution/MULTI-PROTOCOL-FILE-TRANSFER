#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 8080

void send_file(int client_socket, const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (send(client_socket, buffer, bytes_read, 0) != bytes_read) {
            printf("Error sending file\n");
            break;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    int port = DEFAULT_PORT;
    if (argc > 2) {
        printf("Usage: %s [port]\n", argv[0]);
        return 1;
    } else if (argc == 2) {
        port = atoi(argv[1]);
    }

    int socket_desc, client_socket, c;
    struct sockaddr_in server, client;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Bind failed\n");
        return 1;
    }
    printf("Bind done\n");

    // Listen
    listen(socket_desc, 3);

    // Accept incoming connections
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
    while ((client_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
        printf("Connection accepted\n");

        char request[BUFFER_SIZE];
        int bytes_received = recv(client_socket, request, BUFFER_SIZE, 0);
        if (bytes_received < 0) {
            printf("Receive failed\n");
            close(client_socket);
            continue;
        }

        // Parse HTTP request
        char method[10], path[255];
        sscanf(request, "%s %s", method, path);

        // Send HTTP response
        if (strcmp(method, "GET") == 0) {
            printf("GET request for %s\n", path);
            send_file(client_socket, path + 1); // Skip the leading '/'
        } else {
            printf("Unsupported method: %s\n", method);
        }

        // Close the socket
        close(client_socket);
        printf("Connection closed\n");
    }

    if (client_socket < 0) {
        printf("Accept failed\n");
        return 1;
    }

    return 0;
}
