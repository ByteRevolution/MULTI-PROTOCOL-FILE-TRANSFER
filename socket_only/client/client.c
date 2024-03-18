 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <libgen.h> // For basename function

#define PORT 8080
#define LCL_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("Usage: %s SERVER_IP <filename>\n", argv[0]);
        printf("No IP will configure localhost as a server \n");
        return 1;
	}	

    if( !(strcmp(argv[1],"--help")) || !(strcmp(argv[1],"-h")) ){
        printf("Usage: %s SERVER_IP <filename>\n", argv[0]);
        printf("No IP will configure localhost as a server \n");
        return 1;
    }

    if (argc != 3 && argc != 2) {
        printf("Usage: %s SERVER_IP <filename>\n", argv[0]);
        printf("No IP will configure localhost as a server \n");
        return 1;
    }

    FILE *file;

    if(argc == 3){
        file = fopen(argv[2], "rb");
    }

    if(argc == 2){
        file = fopen(argv[1], "rb");
    }

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
    if(argc == 2){
        
        if (inet_pton(AF_INET, LCL_IP, &serv_addr.sin_addr) <= 0) {
            perror("Invalid address/ Address not supported");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    if(argc == 3){
        
        if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
            perror("Invalid address/ Address not supported");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }
/**


    // Call the shell script to add the client IP to UFW allow list
    char command[256];
    snprintf(command, sizeof(command), "./allow.sh %s", argv[1]);
    system(command);

*///

    	char command[256];
	snprintf(command, sizeof(command), "sudo ufw allow from  %s", argv[1]);
	system(command);
	system("sudo ufw reload");



    // Send filename to server
    char *filename;
    if (argc == 2) {
        filename = basename(argv[1]);
    } else {
        filename = basename(argv[2]);
    }

    char delimiter[] = "00000000001111111111"; // Delimiter sequence
    size_t delimiter_length = strlen(delimiter);

    // Send filename followed by delimiter sequence
    send(sock, filename, strlen(filename), 0);
    send(sock, delimiter, delimiter_length, 0);

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
