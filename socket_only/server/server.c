// Server side
// (Accept connection, receive file, close connection)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <libgen.h> // For basename function

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    system("sudo ufw disable");
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to localhost:PORT
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }



char filename[BUFFER_SIZE];
ssize_t filename_length = 0;

while (1) {
    ssize_t bytes_received = recv(new_socket, filename + filename_length, 1, 0); // Receive one byte at a time
    if (bytes_received <= 0) {
        perror("Failed to receive file path");
        exit(EXIT_FAILURE);
    }

    // Check if we received the delimiter (e.g., 10 zeros followed by 10 ones)
    if (filename_length >= 20 && memcmp(filename + filename_length - 20, "00000000001111111111", 20) == 0) {
        filename_length -= 20; // Remove the delimiter from the filename
        filename[filename_length] = '\0'; // Null terminate the filename
        break; // Stop receiving filename
    }

    filename_length++; // Increment filename length
}

printf("Received filename: %s\n", filename);

// Open file with the received filename for writing
FILE *file = fopen(filename, "wb");
if (!file) {
    perror("File creation failed");
    exit(EXIT_FAILURE);
}

// Receive and write file content
ssize_t bytes_received;
while ((bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0)) > 0) {
    fwrite(buffer, 1, bytes_received, file);
}

if (bytes_received < 0) {
    perror("Receive failed");
    exit(EXIT_FAILURE);
}

// Close file and connection
fclose(file);
close(new_socket);
close(server_fd);
    
    system("sudo ufw enable");

    return 0;
}
