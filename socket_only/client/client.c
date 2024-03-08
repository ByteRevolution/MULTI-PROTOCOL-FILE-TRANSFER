// Client side
// (Establish connection, send filename and file content, close connection)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <libgen.h> // For basename function

#define PORT 8080
#define IP "192.168.2.210"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("File opening failed");
        return 1;
    }

    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Send filename to server
    char *filename = basename(argv[1]);
    send(sock, filename, strlen(filename), 0);

    // Read and send file content
    size_t bytes_read;
    char buffer[BUFFER_SIZE];
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(sock, buffer, bytes_read, 0);
    }

    // Close file and socket
    fclose(file);
    close(sock);
    return 0;
}
