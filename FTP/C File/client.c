#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char ftp_server_ip[100];
    char username[100];
    char password[100];

    // Check if ftp client is installed
    if (system("which ftp > /dev/null 2>&1") != 0) {
        printf("ftp client is not installed. Installing...\n");
        system("sudo apt-get update");
        system("sudo apt-get install -y ftp");
    } else {
        printf("ftp client is already installed.\n");
    }

    // Ask for FTP server IP
    printf("Enter FTP server IP address: ");
    fgets(ftp_server_ip, sizeof(ftp_server_ip), stdin);
    strtok(ftp_server_ip, "\n"); // Remove trailing newline

    // Ask for username and password if needed
    printf("Enter username (press Enter if not needed): ");
    fgets(username, sizeof(username), stdin);
    strtok(username, "\n"); // Remove trailing newline

    printf("Enter password (press Enter if not needed): ");
    fgets(password, sizeof(password), stdin);
    strtok(password, "\n"); // Remove trailing newline

    // Connect to FTP server
    printf("Connecting to FTP server %s", ftp_server_ip);
    if (strlen(username) > 0) {
        printf(" with username %s...\n", username);
        FILE *ftp_commands = fopen("ftp_commands.txt", "w");
        fprintf(ftp_commands, "quote USER %s\n", username);
        fprintf(ftp_commands, "quote PASS %s\n", password);
        fprintf(ftp_commands, "quit\n");
        fclose(ftp_commands);
        system("ftp -n < ftp_commands.txt");
        remove("ftp_commands.txt");
    } else {
        printf("...\n");
        system("echo 'quit' | ftp -n $ftp_server_ip");
    }

    printf("FTP connection completed.\n");

    return 0;
}
